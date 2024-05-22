import aff3ct

aff3ct.rang.enable_colors()

import argparse
import time
import pytest

aff3ct.Signal_handler.init()
HW_CONCURRENCY = aff3ct._ext.get_hardware_concurrency()


@pytest.mark.parametrize("cyclic_path", [False, True])
@pytest.mark.parametrize("debug", [False])
@pytest.mark.parametrize("step_by_step", [False, True])
@pytest.mark.parametrize("print_stats", [False])
@pytest.mark.parametrize("copy_mode", [False, True])
@pytest.mark.parametrize("dot_filepath", [""])
@pytest.mark.parametrize("path", [0, 1, 2])
@pytest.mark.parametrize("n_exec", [100])
@pytest.mark.parametrize("data_length", [2048])
@pytest.mark.parametrize("sleep_time_us", [5])
@pytest.mark.parametrize("n_inter_frames", [1, 4])
@pytest.mark.parametrize("n_threads", [HW_CONCURRENCY])
def test_exclusive_paths(
    n_threads: int,
    n_inter_frames: int,
    sleep_time_us: int,
    data_length: int,
    n_exec: int,
    path: int,
    dot_filepath: str,
    copy_mode: bool,
    print_stats: bool,
    step_by_step: bool,
    debug: bool,
    cyclic_path: bool,
):
    assert exclusive_paths(
        n_threads,
        n_inter_frames,
        sleep_time_us,
        data_length,
        n_exec,
        path,
        dot_filepath,
        copy_mode,
        print_stats,
        step_by_step,
        debug,
        cyclic_path,
    )


def exclusive_paths(
    n_threads: int = HW_CONCURRENCY,
    n_inter_frames: int = 1,
    sleep_time_us: int = 5,
    data_length: int = 2048,
    n_exec: int = 100,
    path: int = 0,
    dot_filepath: str = "",
    copy_mode: bool = False,
    print_stats: bool = False,
    step_by_step: bool = False,
    debug: bool = False,
    cyclic_path: bool = False,
):

    print("####################################")
    print("# Micro-benchmark: Exclusive Paths #")
    print("####################################")
    print("#")
    print("# Command line arguments:")
    print(f"#   - n_threads      = {n_threads}")
    print(f"#   - n_inter_frames = {n_inter_frames}")
    print(f"#   - sleep_time_us  = {sleep_time_us}")
    print(f"#   - data_length    = {data_length}")
    print(f"#   - n_exec         = {n_exec}")
    print(f"#   - path           = {path}")
    print(f"#   - dot_filepath   = {dot_filepath if dot_filepath else 'empty'}")
    print(f"#   - no_copy_mode   = {not copy_mode}")
    print(f"#   - print_stats    = {print_stats}")
    print(f"#   - step_by_step   = {step_by_step}")
    print(f"#   - debug          = {debug}")
    print(f"#   - cyclic_path    = {cyclic_path}")
    print("#")

    if path >= 3:
        raise aff3ct.exceptions.InvalidArgument("'path' has to be smaller than 3")

    controller = None
    if cyclic_path:
        controller = aff3ct.Controller_cyclic(3, 0)
    else:
        controller = aff3ct.Controller_static(path)

    switcher = aff3ct.Switcher(3, data_length, aff3ct.uint8)
    initializer = aff3ct.initializer(data_length, dtype=aff3ct.uint8)
    finalizer = aff3ct.finalizer(data_length, dtype=aff3ct.uint8)

    incs = []
    for s in range(6):
        inc = aff3ct.incrementer(data_length, dtype=aff3ct.uint8)
        inc.ns = sleep_time_us * 1000
        inc.name = "Inc" + str(s)
        incs.append(inc)

    data = initializer.initialize()
    controller.control.bind(data)
    the_path = controller.control()

    sw_path0, sw_path1, sw_path2 = switcher.commute(data, the_path)
    inc_data0 = incs[0].increment(sw_path0)
    inc_data0 = incs[1].increment(inc_data0)
    inc_data0 = incs[2].increment(inc_data0)

    inc_data1 = incs[3].increment(sw_path1)
    inc_data1 = incs[4].increment(inc_data1)

    inc_data2 = incs[5].increment(sw_path2)

    inc_data = switcher.select(inc_data0, inc_data1, inc_data2)
    finalizer.finalize(inc_data)

    controller.reset()

    sequence_chain = aff3ct.Sequence(data.task, n_threads)
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

    start = time.time_ns()

    if not step_by_step:
        sequence_chain.exec_n_times(n_exec)
    else:
        start = time.time_ns()
        counter = 0
        while counter < n_exec / n_threads:
            for tid in range(n_threads):
                while sequence_chain.exec_step(tid):
                    pass
            counter += 1

    stop = time.time_ns()
    duration = (stop - start) / 1000000.0

    chain_sleep_time = 0
    for inc in incs:
        chain_sleep_time += inc.ns

    multipliers = [2, 3, 6]
    real_path = 1 if cyclic_path else path
    theoretical_time = (
        ((chain_sleep_time / multipliers[real_path]) * n_exec * n_inter_frames)
        / 1000000.0
        / n_threads
    )

    print(f"Sequence elapsed time: {duration} ms")
    print(f"Sequence theoretical time: {theoretical_time} ms")

    tests_passed = True

    tid = 0
    for cur_finalizer in sequence_chain.get_cloned_modules(finalizer):
        real_path = path
        if cyclic_path:
            real_path = (cur_finalizer.finalize.n_calls - 1) % 3
        for f in range(n_inter_frames):
            final_data = cur_finalizer.final_data[f]
            for d in range(len(final_data)):
                expected = len(incs) / multipliers[real_path] + tid * n_inter_frames + f
                expected = expected % 256
                if final_data[d] != expected:
                    print(
                        f"# expected = {expected} - obtained = {final_data[d]} (d = {d}, tid = {tid})"
                    )
                    tests_passed = False
        tid += 1
    if print_stats:
        print("#")
        sequence_chain.show_stats(True, False)

    if tests_passed:
        print(
            f"#{aff3ct.rang.style.bold}{aff3ct.rang.fg.green} Tests passed! {aff3ct.rang.style.reset}"
        )
    else:
        print(
            f"#{aff3ct.rang.style.bold}{aff3ct.rang.fg.red} Tests failed :-( {aff3ct.rang.style.reset}"
        )
    return tests_passed


if __name__ == "__main__":
    max_threads = aff3ct._ext.get_hardware_concurrency()

    parser = argparse.ArgumentParser(
        description="Test a simple AFF3CT chain.",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )

    parser.add_argument(
        "-t",
        "--n-threads",
        type=int,
        dest="n_threads",
        default=max_threads,
        help="Number of threads to run in parallel",
    )
    parser.add_argument(
        "-f",
        "--n-inter-frames",
        type=int,
        dest="n_inter_frames",
        default=1,
        help="Number of frames to process in one task",
    )
    parser.add_argument(
        "-s",
        "--sleep-time",
        type=int,
        dest="sleep_time_us",
        default=5,
        help="Sleep time duration in one task (microseconds)",
    )
    parser.add_argument(
        "-d",
        "--data-length",
        type=int,
        dest="data_length",
        default=2048,
        help="Size of data to process in one task (in bytes)",
    )
    parser.add_argument(
        "-e",
        "--n-exec",
        type=int,
        dest="n_exec",
        default=100000,
        help="Number of sequence executions",
    )
    parser.add_argument(
        "-a",
        "--path",
        type=int,
        dest="path",
        default=0,
        help="Path to take in the switch (0, 1 or 2)",
    )
    parser.add_argument(
        "-o",
        "--dot-filepath",
        type=str,
        dest="dot_filepath",
        default="",
        help="Path to dot output file",
    )

    parser.add_argument(
        "-c",
        "--copy-mode",
        action="store_true",
        dest="copy_mode",
        default=False,
        help="Enable to copy data in sequence (performance will be reduced)",
    )
    parser.add_argument(
        "-p",
        "--print-stats",
        action="store_true",
        dest="print_stats",
        default=False,
        help="Enable to print per task statistics (performance will be reduced)",
    )
    parser.add_argument(
        "-b",
        "--step-by-step",
        action="store_true",
        dest="step_by_step",
        default=False,
        help="Enable step-by-step sequence execution (performance will be reduced)",
    )
    parser.add_argument(
        "-g",
        "--debug",
        action="store_true",
        dest="debug",
        default=False,
        help="Enable task debug mode (print socket data)",
    )
    parser.add_argument(
        "-y",
        "--cyclic-path",
        action="store_true",
        dest="cyclic_path",
        default=False,
        help="Enable cyclic selection of the path (with this '--path' is ignored)   ",
    )
    args = parser.parse_args()

    exclusive_paths(**vars(args))
