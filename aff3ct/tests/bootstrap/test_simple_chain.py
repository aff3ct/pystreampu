import aff3ct
import argparse
import time
import pytest

aff3ct.Signal_handler.init()
HW_CONCURRENCY  = aff3ct._ext.get_hardware_concurrency()

@pytest.mark.parametrize("verbose", [False])
@pytest.mark.parametrize("set", [False, True])
@pytest.mark.parametrize("debug", [False])
@pytest.mark.parametrize("step_by_step", [False, True])
@pytest.mark.parametrize("print_stats", [False])
@pytest.mark.parametrize("copy_mode", [False, True])
@pytest.mark.parametrize("dot_filepath", [''])
@pytest.mark.parametrize("n_exec", [100])
@pytest.mark.parametrize("data_length", [2048])
@pytest.mark.parametrize("sleep_time_us", [5])
@pytest.mark.parametrize("n_inter_frames", [1])
@pytest.mark.parametrize("n_threads", [HW_CONCURRENCY])
def test_simple_chain(n_threads:int,
                      n_inter_frames:int,
                      sleep_time_us:int,
                      data_length:int,
                      n_exec:int,
                      dot_filepath:str,
                      copy_mode:bool,
                      print_stats:bool,
                      step_by_step:bool,
                      debug:bool,
                      set:bool,
                      verbose:bool):
    assert simple_chain(n_threads, n_inter_frames, sleep_time_us, data_length,
                        n_exec, dot_filepath, copy_mode, print_stats,
                        step_by_step, debug, set, verbose)


def simple_chain(n_threads:int = HW_CONCURRENCY,
                 n_inter_frames:int = 1,
                 sleep_time_us:int = 5,
                 data_length:int = 2048,
                 n_exec:int = 100,
                 dot_filepath:str = '',
                 copy_mode:bool = False,
                 print_stats:bool = False,
                 step_by_step:bool = False,
                 debug:bool = False,
                 set:bool = False,
                 verbose:bool = False):

    print("#################################")
    print("# Micro-benchmark: Simple chain #")
    print("#################################")
    print("#")
    print("# Command line arguments:")
    print(f"#   - n_threads      = {n_threads}")
    print(f"#   - n_inter_frames = {n_inter_frames}")
    print(f"#   - sleep_time_us  = {sleep_time_us}")
    print(f"#   - data_length    = {data_length}")
    print(f"#   - n_exec         = {n_exec}")
    print(f"#   - dot_filepath   = {dot_filepath if dot_filepath else 'empty'}")
    print(f"#   - no_copy_mode   = {not copy_mode}")
    print(f"#   - print_stats    = {print_stats}")
    print(f"#   - step_by_step   = {step_by_step}")
    print(f"#   - debug          = {debug}")
    print(f"#   - set            = {set}")
    print(f"#   - verbose        = {verbose}")
    print("#")

    initializer = aff3ct.initializer(data_length, dtype=aff3ct.uint8)
    finalizer   = aff3ct.finalizer  (data_length, dtype=aff3ct.uint8)

    incs = []
    for s in range(6):
        inc = aff3ct.incrementer(data_length, dtype=aff3ct.uint8)
        inc.ns = sleep_time_us * 1000
        inc.name = "Inc" + str(s)
        incs.append(inc)

    if not set:
        x = initializer.initialize()
        y = incs[0].increment(x)
        for i in range(1,6):
            y = incs[i].increment(y)
        finalizer.finalize(y)
    else:
        for i in range(0,5):
            incs[i+1]["increment::in"] = incs[i]["increment::out"]
        partial_sequence = aff3ct.Sequence(incs[0].increment, incs[len(incs)-1].increment)
        theset = aff3ct.Set(partial_sequence)
        x = initializer.initialize()
        y = theset.exec(x)
        finalizer.finalize(y)

    sequence_chain = aff3ct.Sequence(x.task, n_threads)
    sequence_chain.n_frames = n_inter_frames
    sequence_chain.no_copy_mode = not copy_mode

    if dot_filepath:
        sequence_chain.export_dot(dot_filepath)

    for mdl in sequence_chain.get_modules(aff3ct.Module, False):
        for tsk in mdl.tasks:
            tsk.reset()
            tsk.debug = debug
            tsk.set_debug_limit(16)
            tsk.stats = print_stats
            tsk.fast = True
    tid = 0
    cloned_initializers = sequence_chain.get_cloned_modules(initializer)
    for cur_initializer in cloned_initializers:
        for f in range(n_inter_frames):
            cur_initializer.data_init[f][:] = tid * n_inter_frames + f
        tid += 1

    if verbose:
        print()
        print("Helper information:")
        print("-------------------")
        aff3ct.help(initializer)
        for inc in incs:
            aff3ct.help(inc)
        aff3ct.help(finalizer)

    start = time.time_ns()

    if not step_by_step:
        sequence_chain.exec_n_times(n_exec)
    else:
        start = time.time_ns()
        counter = 0
        while counter < n_exec/n_threads:
            for tid in range(n_threads):
                while sequence_chain.exec_step(tid):
                    pass
            counter += 1

    stop = time.time_ns()
    duration = (stop - start) / 1000000.0

    chain_sleep_time = 0
    for inc in incs:
        chain_sleep_time += inc.ns

    theoretical_time = (chain_sleep_time * n_exec * n_inter_frames) / 1000000.0 / n_threads

    print(f"Sequence elapsed time: {duration} ms")
    print(f"Sequence theoretical time: {theoretical_time} ms")

    tests_passed = True

    tid = 0
    for cur_finalizer in sequence_chain.get_cloned_modules(finalizer):
        for f in range(n_inter_frames):
            final_data = cur_finalizer.final_data[f]
            for d in range(len(final_data)):
                expected = len(incs) + tid * n_inter_frames +f
                expected = expected % 256
                if final_data[d] != expected:
                    print(f"# expected = {expected} - obtained = {final_data[d]} (d = {d}, tid = {tid})")
                    tests_passed = False
        tid+=1
    if print_stats:
        print("#")
        sequence_chain.show_stats(True, False)

    if (tests_passed):
        print(f"#{aff3ct.rang.style.bold}{aff3ct.rang.fg.green} Tests passed! {aff3ct.rang.style.reset}")
    else:
        print(f"#{aff3ct.rang.style.bold}{aff3ct.rang.fg.red} Tests failed :-( {aff3ct.rang.style.reset}")

    return tests_passed

if __name__ == '__main__':
    max_threads = aff3ct._ext.get_hardware_concurrency()

    parser = argparse.ArgumentParser(description='Test a simple AFF3CT chain.', formatter_class=argparse.ArgumentDefaultsHelpFormatter)

    parser.add_argument('-t', '--n-threads',      type = int, dest = 'n_threads',      default = max_threads, help = 'Number of threads to run in parallel')
    parser.add_argument('-f', '--n-inter-frames', type = int, dest = 'n_inter_frames', default = 1,           help = 'Number of frames to process in one task')
    parser.add_argument('-s', '--sleep-time',     type = int, dest = 'sleep_time_us',  default = 5,           help = 'Sleep time duration in one task (microseconds)')
    parser.add_argument('-d', '--data-length',    type = int, dest = 'data_length',    default = 2048,        help = 'Size of data to process in one task (in bytes)')
    parser.add_argument('-e', '--n-exec',         type = int, dest = 'n_exec',         default = 100000,      help = 'Number of sequence executions')
    parser.add_argument('-o', '--dot-filepath',   type = str, dest = 'dot_filepath',   default = '',          help = 'Path to dot output file')

    parser.add_argument('-c', '--copy-mode',    action='store_true', dest = 'copy_mode',    default = False, help = 'Enable to copy data in sequence (performance will be reduced)')
    parser.add_argument('-p', '--print-stats',  action='store_true', dest = 'print_stats',  default = False, help = 'Enable to print per task statistics (performance will be reduced)')
    parser.add_argument('-b', '--step-by-step', action='store_true', dest = 'step_by_step', default = False, help = 'Enable step-by-step sequence execution (performance will be reduced)')
    parser.add_argument('-g', '--debug',        action='store_true', dest = 'debug',        default = False, help = 'Enable task debug mode (print socket data)')
    parser.add_argument('-u', '--set',          action='store_true', dest = 'set',          default = False, help = 'Enable set in the executed sequence')
    parser.add_argument('-v', '--verbose',      action='store_true', dest = 'verbose',      default = False, help = 'Enable verbose mode')

    args = parser.parse_args()

    simple_chain(**vars(args))