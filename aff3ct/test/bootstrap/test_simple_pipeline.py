import aff3ct
import aff3ct.rang as rang
import argparse
import filecmp
from math import ceil
import os
import time
import pytest
import contextlib

aff3ct.setup_signal_handler()
HW_CONCURRENCY  = aff3ct._ext.get_hardware_concurrency()

@pytest.mark.parametrize("n_threads", [HW_CONCURRENCY])
@pytest.mark.parametrize("n_inter_frames", [1, 4])
@pytest.mark.parametrize("sleep_time_us", [5])
@pytest.mark.parametrize("data_length", [2048])
@pytest.mark.parametrize("buffer_size", [16])
@pytest.mark.parametrize("dot_filepath", [''])
@pytest.mark.parametrize("in_filepath", ['file.in'])
@pytest.mark.parametrize("out_filepath", ['file.out'])
@pytest.mark.parametrize("copy_mode", [False])
@pytest.mark.parametrize("print_stats", [False])
@pytest.mark.parametrize("step_by_step", [False])
@pytest.mark.parametrize("debug", [False])
@pytest.mark.parametrize("force_sequence", [False])
@pytest.mark.parametrize("active_waiting", [False])
def test_simple_pipeline(n_threads:int,
                         n_inter_frames:int,
                         sleep_time_us:int,
                         data_length:int,
                         buffer_size:int,
                         dot_filepath:str,
                         in_filepath:str,
                         out_filepath:str,
                         copy_mode:bool,
                         print_stats:bool,
                         step_by_step:bool,
                         debug:bool,
                         force_sequence:bool,
                         active_waiting:bool):
    os.system(f'head -c 1048576 </dev/urandom >{in_filepath}')
    test_result = simple_pipeline(n_threads, n_inter_frames, sleep_time_us, data_length,
                                  buffer_size, dot_filepath, in_filepath, out_filepath, copy_mode, print_stats,
                                  step_by_step, debug, force_sequence, active_waiting)
    os.system(f'rm {in_filepath}')
    assert test_result



def repl_empty(input:str):
    return input if input else '[empty]'



def simple_pipeline(n_threads:int = HW_CONCURRENCY-2,
                    n_inter_frames:int = 1,
                    sleep_time_us:int = 5,
                    data_length:int = 2048,
                    buffer_size:int = 16,
                    dot_filepath:str = '',
                    in_filepath:str = '',
                    out_filepath:str = 'file.out',
                    copy_mode:bool = False,
                    print_stats:bool = False,
                    step_by_step:bool = False,
                    debug:bool = False,
                    force_sequence:bool = False,
                    active_waiting:bool = False):

    print("####################################")
    print("# Micro-benchmark: Simple pipeline #")
    print("####################################")
    print("#")
    print("# Command line arguments:")
    print(f"#   - n_threads      = {n_threads}")
    print(f"#   - n_inter_frames = {n_inter_frames}")
    print(f"#   - sleep_time_us  = {sleep_time_us}")
    print(f"#   - data_length    = {data_length}")
    print(f"#   - buffer_size    = {buffer_size}")
    print(f"#   - dot_filepath   = {repl_empty(dot_filepath)}")
    print(f"#   - in_filepath    = {repl_empty(in_filepath)}")
    print(f"#   - out_filepath   = {repl_empty(out_filepath)}")
    print(f"#   - no_copy_mode   = {not copy_mode}")
    print(f"#   - print_stats    = {print_stats}")
    print(f"#   - step_by_step   = {step_by_step}")
    print(f"#   - debug          = {debug}")
    print(f"#   - force_sequence = {force_sequence}")
    print(f"#   - active_waiting = {active_waiting}")
    print("#")

    if not force_sequence and copy_mode:
        print(rang.warning_tag("'no_copy_mode' has no effect with pipeline (it is always enable)"))
    if not force_sequence and step_by_step:
        print(rang.warning_tag("'step_by_step' is not available with pipeline"))
    if force_sequence and n_threads > 1:
        print(rang.warning_tag("Sequence mode only supports a single thread (User-Source/Sinks are not clonable)"))
        n_threads = 1


    source = aff3ct.source_user_binary(data_length, in_filepath, auto_reset=False, dtype=aff3ct.uint8)
    sink = aff3ct.sink_user_binary(data_length, out_filepath, dtype=aff3ct.uint8)

    rlys = []
    for s in range(6):
        rly = aff3ct.relayer(data_length, dtype=aff3ct.uint8)
        rly.ns = sleep_time_us * 1000
        rly.name = "Relayer" + str(s)
        rlys.append(rly)

    aff3ct.Task.call_auto_exec = False
    [data, cnt] = source.generate()
    for i in range(6):
        data = rlys[i].relay(data)
    sink.send_count(data, cnt)

    sequence_chain = None
    pipeline_chain = None
    duration = 0
    if force_sequence:
        sequence_chain = aff3ct.Sequence(source.generate, n_threads)
        if dot_filepath:
            sequence_chain.export_dot('sequence.dot')
        sequence_chain.n_frames = n_inter_frames
        sequence_chain.no_copy_mode = not copy_mode
        for mdl in sequence_chain.get_modules(aff3ct.Module, False):
            for tsk in mdl.tasks:
                tsk.reset()
                tsk.debug = debug
                tsk.set_debug_limit(16)
                tsk.stats = print_stats
                tsk.fast = True

        start = time.time_ns()
        if not step_by_step:
            sequence_chain.exec()
        else:
            while not source.is_done():
                try:
                    for tid in range(n_threads):
                        while sequence_chain.exec_step(tid):
                            pass
                except aff3ct.exceptions.ProcessingAborted:
                    pass

        stop = time.time_ns()
        duration = (stop - start) / 1000000.0
    else:
        pipeline_chain = aff3ct.Pipeline(
            [source.generate],
            [sink.send_count],
            [[[source.generate], [source.generate], []],
             [[rlys[0].relay  ], [rlys[-1].relay ], []],
             [[sink.send_count], [sink.send_count], []]],
            [1, n_threads, 1],
            [buffer_size]*2,
            [active_waiting]*2)

        pipeline_chain.n_frames = n_inter_frames

        if dot_filepath:
            pipeline_chain.export_dot(dot_filepath)

        for mdl in pipeline_chain.get_modules(aff3ct.Module, False):
            for tsk in mdl.tasks:
                tsk.reset()
                tsk.debug = debug
                tsk.set_debug_limit(16)
                tsk.stats = print_stats
                tsk.fast = True

        start = time.time_ns()
        pipeline_chain.exec()
        stop = time.time_ns()
        duration = (stop - start) / 1000000.0

    print(f"Sequence elapsed time: {duration} ms")
    in_filesize = os.stat(in_filepath).st_size
    n_frames = ceil(in_filesize * 8.0 / (data_length * n_inter_frames))
    theoretical_time = (n_frames * (len(rlys) * sleep_time_us * 1000) * n_inter_frames) / 1000.0 / 1000.0 / n_threads
    print(f"Sequence theoretical time: {theoretical_time} ms")
    tests_passed = filecmp.cmp(in_filepath, out_filepath)

    if print_stats:
        print("#")
        if force_sequence:
            pass
        else:
            pipeline_chain.show_stats()

    if (tests_passed):
        print(f"#{rang.style.bold}{rang.fg.green} Tests passed! {rang.style.reset}")
    else:
        print(f"#{rang.style.bold}{rang.fg.red} Tests failed :-( {rang.style.reset}")

    aff3ct.Task.call_auto_exec = True
    return tests_passed


if __name__ == '__main__':
    max_threads = aff3ct._ext.get_hardware_concurrency()

    parser = argparse.ArgumentParser(description='Test a simple AFF3CT chain.', formatter_class=argparse.ArgumentDefaultsHelpFormatter)

    parser.add_argument('-t', '--n-threads',      type = int, dest = 'n_threads',      default = max_threads-2, help = 'Number of threads to run in parallel')
    parser.add_argument('-f', '--n-inter-frames', type = int, dest = 'n_inter_frames', default = 1,             help = 'Number of frames to process in one task')
    parser.add_argument('-s', '--sleep-time',     type = int, dest = 'sleep_time_us',  default = 5,             help = 'Sleep time duration in one task (microseconds)')
    parser.add_argument('-d', '--data-length',    type = int, dest = 'data_length',    default = 2048,          help = 'Size of data to process in one task (in bytes)')
    parser.add_argument('-u', '--buffer-size',    type = int, dest = 'buffer_size',    default = 16,            help = 'Size of the buffer between the different stages of the pipeline')
    parser.add_argument('-o', '--dot-filepath',   type = str, dest = 'dot_filepath',   default = '',            help = 'Path to dot output file')
    parser.add_argument('-i', '--in-filepath',    type = str, dest = 'in_filepath',    default = '',            help = 'Path to dot input file')
    parser.add_argument('-j', '--out-filepath',   type = str, dest = 'out_filepath',   default = 'file.out',    help = 'Path to dot input file')
    parser.add_argument('-c', '--copy-mode',     action='store_true', dest = 'copy_mode',     default = False, help = 'Enable to copy data in sequence (performance will be reduced)')
    parser.add_argument('-p', '--print-stats',   action='store_true', dest = 'print_stats',   default = False, help = 'Enable to print per task statistics (performance will be reduced)')
    parser.add_argument('-b', '--step-by-step',  action='store_true', dest = 'step_by_step',  default = False, help = 'Enable step-by-step sequence execution (performance will be reduced)')
    parser.add_argument('-g', '--debug',         action='store_true', dest = 'debug',         default = False, help = 'Enable task debug mode (print socket data)')
    parser.add_argument('-q', '--force-sequence',action='store_true', dest = 'force_sequence',default = False, help = 'Force sequence instead of pipeline')
    parser.add_argument('-w', '--active_wating', action='store_true', dest = 'active_waiting',default = False, help = 'Enable active waiting in the pipeline synchronizations')

    args = parser.parse_args()

    simple_pipeline(**vars(args))
