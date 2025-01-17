# -*- coding: utf-8 -*-
"""Python implementation of StreamPU For loop test."""
import argparse
import time

import pytest

import streampu

streampu.Signal_handler.init()
HW_CONCURRENCY = streampu._ext.get_hardware_concurrency()


@pytest.mark.parametrize("n_threads", [HW_CONCURRENCY])
@pytest.mark.parametrize("n_inter_frames", [1, 4])
@pytest.mark.parametrize("sleep_time_us", [5])
@pytest.mark.parametrize("data_length", [2048])
@pytest.mark.parametrize("n_exec", [100])
@pytest.mark.parametrize("n_loop", [9, 13])
@pytest.mark.parametrize("dot_filepath", [""])
@pytest.mark.parametrize("copy_mode", [False, True])
@pytest.mark.parametrize("print_stats", [False])
@pytest.mark.parametrize("step_by_step", [False, True])
@pytest.mark.parametrize("debug", [False])
@pytest.mark.parametrize("cpp_binding", [False, True])
def test_for_loop(
    n_threads: int,
    n_inter_frames: int,
    sleep_time_us: int,
    data_length: int,
    n_exec: int,
    n_loop: int,
    dot_filepath: str,
    copy_mode: bool,
    print_stats: bool,
    step_by_step: bool,
    debug: bool,
    cpp_binding: bool,
):
    """For loop test.

    Args:
        n_threads (int): number of threads to run in parallel
        n_inter_frames (int): number of frames to process in one task
        sleep_time_us (int): sleep time duration in one task (microseconds)
        data_length (int): size of data to process in one task (in bytes)
        n_exec (int): number of sequence executions
        n_loop (int): number of iterations to perform in the loop
        dot_filepath (str): path to dot output file
        copy_mode (bool): enable to copy data in sequence (performance will be reduced)
        print_stats (bool): enable to print per task statistics (performance will be reduced)
        step_by_step (bool): enable step-by-step sequence execution (performance will be reduced)
        debug (bool): Enable task debug mode (print socket data)
        cpp_binding (bool): perform binding with C++ style
    """
    assert for_loop(
        n_threads,
        n_inter_frames,
        sleep_time_us,
        data_length,
        n_exec,
        n_loop,
        dot_filepath,
        copy_mode,
        print_stats,
        step_by_step,
        debug,
        cpp_binding,
    )


def for_loop(
    n_threads: int = HW_CONCURRENCY,
    n_inter_frames: int = 1,
    sleep_time_us: int = 5,
    data_length: int = 2048,
    n_exec: int = 100,
    n_loop: int = 9,
    dot_filepath: str = "",
    copy_mode: bool = False,
    print_stats: bool = False,
    step_by_step: bool = False,
    debug: bool = False,
    cpp_binding: bool = False,
):
    """For loop test.

    Args:
        n_threads (int): number of threads to run in parallel
        n_inter_frames (int): number of frames to process in one task
        sleep_time_us (int): sleep time duration in one task (microseconds)
        data_length (int): size of data to process in one task (in bytes)
        n_exec (int): number of sequence executions
        n_loop (int): number of iterations to perform in the loop
        dot_filepath (str): path to dot output file
        copy_mode (bool): enable to copy data in sequence (performance will be reduced)
        print_stats (bool): enable to print per task statistics (performance will be reduced)
        step_by_step (bool): enable step-by-step sequence execution (performance will be reduced)
        debug (bool): Enable task debug mode (print socket data)
        cpp_binding (bool): perform binding with C++ style

    Returns:
        out (bool): Test status
    """
    print("#############################")
    print("# Micro-benchmark: For loop #")
    print("#############################")
    print("#")
    print("# Command line arguments:")
    print(f"#   - n_threads      = {n_threads}")
    print(f"#   - n_inter_frames = {n_inter_frames}")
    print(f"#   - sleep_time_us  = {sleep_time_us}")
    print(f"#   - data_length    = {data_length}")
    print(f"#   - n_exec         = {n_exec}")
    print(f"#   - n_loop         = {n_loop}")
    print(f"#   - dot_filepath   = {dot_filepath if dot_filepath else 'empty'}")
    print(f"#   - no_copy_mode   = {not copy_mode}")
    print(f"#   - print_stats    = {print_stats}")
    print(f"#   - step_by_step   = {step_by_step}")
    print(f"#   - debug          = {debug}")
    print(f"#   - binding_style  = {'C++' if cpp_binding else 'Python'}")
    print("#")

    switcher = streampu.Switcher(2, data_length, streampu.uint8)
    iterator = streampu.Iterator(n_loop)
    initializer = streampu.initializer(data_length, dtype=streampu.uint8)
    finalizer = streampu.finalizer(data_length, dtype=streampu.uint8)

    start = time.time_ns()
    incs = []
    for s in range(6):
        inc = streampu.incrementer(data_length, dtype=streampu.uint8)
        inc.ns = sleep_time_us * 1000
        inc.name = "Inc" + str(s)
        incs.append(inc)
    if cpp_binding:
        switcher["select::in_data1"] = initializer["initialize::out"]
        iterator["iterate"] = switcher["select"]
        switcher["commute::in_data"] = switcher["select::out_data"]
        switcher["commute::in_ctrl"] = iterator["iterate::out"]
        incs[0]["increment::in"] = switcher["commute::out_data0"]
        for i in range(5):
            incs[i + 1]["increment::in"] = incs[i]["increment::out"]
        switcher["select::in_data0"] = incs[5]["increment::out"]
        finalizer["finalize::in"] = switcher["commute::out_data1"]
    else:
        streampu.Task.call_auto_exec = False
        ini_data = initializer.initialize()
        iterator.iterate.bind(switcher.select)
        ite = iterator.iterate()
        [com_out_data0, com_out_data1] = switcher.commute(in_data=switcher["select::out_data"], in_ctrl=ite)
        y = incs[0].increment(com_out_data0)
        for i in range(5):
            y = incs[i + 1].increment(y)
        switcher.select(in_data0=y, in_data1=ini_data)
        finalizer.finalize(com_out_data1)
        streampu.Task.call_auto_exec = True
    stop = time.time_ns()
    binding_duration = (stop - start) / 1000000.0
    print(f"Binding elapsed time: {binding_duration} ms")

    sequence_for_loop = streampu.Sequence(initializer["initialize"], n_threads)
    sequence_for_loop.n_frames = n_inter_frames
    sequence_for_loop.no_copy_mode = not copy_mode

    tid = 0
    cloned_initializers = sequence_for_loop.get_cloned_modules(initializer)
    for cur_initializer in cloned_initializers:
        for f in range(n_inter_frames):
            cur_initializer.data_init[f][:] = tid * n_inter_frames + f
        tid += 1

    for mdl in sequence_for_loop.get_modules(streampu.Module, False):
        for tsk in mdl.tasks:
            tsk.reset()
            tsk.debug = debug
            tsk.set_debug_limit(16)
            tsk.stats = print_stats
            tsk.fast = True

    if dot_filepath:
        sequence_for_loop.export_dot(dot_filepath)

    start = time.time_ns()
    if not step_by_step:
        sequence_for_loop.exec_n_times(n_exec)
    else:
        start = time.time_ns()
        counter = 0
        while counter < n_exec / n_threads:
            for tid in range(n_threads):
                while sequence_for_loop.exec_step(tid):
                    pass
            counter += 1

    stop = time.time_ns()
    duration = (stop - start) / 1000000.0
    print(f"Sequence elapsed time: {duration} ms")
    chain_sleep_time = 0
    for inc in incs:
        chain_sleep_time += inc.ns

    theoretical_time = (chain_sleep_time * n_exec * n_inter_frames) / 1000000.0 / n_threads
    theoretical_time *= iterator.limit + 1

    print(f"Sequence theoretical time: {theoretical_time} ms")
    tests_passed = True
    tid = 0
    for cur_finalizer in sequence_for_loop.get_cloned_modules(finalizer):
        for f in range(n_inter_frames):
            final_data = cur_finalizer.final_data[f]
            for d in range(len(final_data)):
                expected = len(incs) * iterator.limit + tid * n_inter_frames + f
                expected = expected % 256
                if final_data[d] != expected:
                    print(f"# expected = {expected} - obtained = {final_data[d]} (d = {d}, tid = {tid})")
                    tests_passed = False
        tid += 1
    if print_stats:
        print("#")
        sequence_for_loop.show_stats(True, False)

    if tests_passed:
        print(f"#{streampu.rang.style.bold}{streampu.rang.fg.green} Tests passed! {streampu.rang.style.reset}")
    else:
        print(f"#{streampu.rang.style.bold}{streampu.rang.fg.red} Tests failed :-( {streampu.rang.style.reset}")

    return tests_passed


if __name__ == "__main__":
    max_threads = streampu._ext.get_hardware_concurrency()

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
        "-i",
        "--n-loop",
        type=int,
        dest="n_loop",
        default=9,
        help="Number of iterations to perform in the loop",
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
        "-m",
        "--cpp_binding",
        action="store_true",
        dest="cpp_binding",
        default=False,
        help="Perform binding with C++ style",
    )

    args = parser.parse_args()

    for_loop(**vars(args))
