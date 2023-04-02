from ..builtins.core import Task, Socket

def getattr(tsk, sck_name):
    try:
        return tsk.module[f"{tsk.name}::{sck_name}"]
    except:
        raise AttributeError(f"'{tsk.__class__.__name__}' object has no attribute '{sck_name}'")

Task.__getattr__ = lambda tsk, attr: getattr(tsk, attr)

def update_dir(tsk):
    from builtins import object
    new_dir = object.__dir__(tsk)
    for t in tsk.sockets:
        new_dir.append(t.name)
    return new_dir

Task.__dir__ = lambda m: update_dir(m)

def task_call(slf, *args, **kwargs):
    str = "Parameters\n----------\n"
    for s in slf.inputs:
        str += f"\t{s.name}: Input of size {s.n_elmts/slf.module.n_frames}\n"
    task_call.__doc__ = str
    mdl = slf.module
    if not hasattr(mdl,"__tag__"):
        mdl.__tag__ = dict.fromkeys([tsk.name for tsk in slf.module.tasks], {})

    inputs  = slf.inputs
    for i in range(len(args)):
        inputs[i].reset()
        inputs[i].bind(args[i])
        mdl.__tag__[slf.name][inputs[i].name] = args[i].task.module

    for k,s in kwargs.items():
        slf[k].reset()
        slf[k].bind(s)
        mdl.__tag__[slf.name][k] = s.task.module

    slf.exec()
    rv = tuple([s for s in slf.outputs if s.name != "status"])
    for v in rv:
        v.__tag__ = mdl
    if len(rv) > 1:
        return rv
    else:
        return rv[0]

Task.__call__ = task_call

__all__ = ["Task"]