import aff3ct
import argparse

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
parser.add_argument('-u', '--subseq',       action='store_true', dest = 'subseq',       default = False, help = 'Enable subsequence in the executed sequence')
parser.add_argument('-v', '--verbose',      action='store_true', dest = 'verbose',      default = False, help = 'Enable verbose mode')

args = parser.parse_args()

print("#################################")
print("# Micro-benchmark: Simple chain #")
print("#################################")
print("#")
print("# Command line arguments:")
print(f"#   - n_threads      = {args.n_threads}")
print(f"#   - n_inter_frames = {args.n_inter_frames}")
print(f"#   - sleep_time_us  = {args.sleep_time_us}")
print(f"#   - data_length    = {args.data_length}")
print(f"#   - n_exec         = {args.n_exec}")
print(f"#   - dot_filepath   = {args.dot_filepath if args.dot_filepath else 'empty'}")
print(f"#   - no_copy_mode   = {not args.copy_mode}")
print(f"#   - print_stats    = {args.print_stats}")
print(f"#   - step_by_step   = {args.step_by_step}")
print(f"#   - debug          = {args.debug}")
print(f"#   - subseq         = {args.subseq}")
print(f"#   - verbose        = {args.verbose}")
print("#")

initializer = aff3ct.initializer(args.data_length)
finalizer   = aff3ct.finalizer  (args.data_length)

incs = []
for s in range(6):
    inc = aff3ct.incrementer(args.data_length)
    inc.ns = args.sleep_time_us * 1000
    inc.name = "Inc" + str(s)
    incs.append(inc)

if not args.subseq:
    x = initializer.initialize()
    y = incs[0].increment(x)
    for i in range(1,6):
        y = incs[i].increment(y)
else:
    print("Not done yet.")

sequence_chain = aff3ct.Sequence(x.task, args.n_threads)

if (args.dot_filepath):
    sequence_chain.export_dot(args.dot_filepath)

for mdl in sequence_chain.get_module(aff3ct.Module, False):
    for tsk in mdl.tasks:
        tsk.reset()
        tsk.debug = args.debug
        tsk.set_debug_limit(16)
        tsk.stats = args.print_stats
        tsk.fast = True

pass