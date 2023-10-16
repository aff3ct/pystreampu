from ..builtins.core import Task, Socket

def ___getattr___(tsk, sck_name):
    try:
        return tsk.module[f"{tsk.name}::{sck_name}"]
    except:
        raise AttributeError(f"'{tsk.__class__.__name__}' object has no attribute '{sck_name}'")

Task.__getattr__ = lambda tsk, attr: ___getattr___(tsk, attr)

def ___dir___(tsk):
    from builtins import object
    new_dir = object.__dir__(tsk)
    for t in tsk.sockets:
        new_dir.append(t.name)
    return new_dir

Task.__dir__ = lambda m: ___dir___(m)

def ___call___(slf, *args, **kwargs):
    inputs  = []
    outputs  = []
    str = "Parameters\n----------\n"
    for s in slf.sockets:
        if s.direction == Socket.directions.IN:
            str += f"\t{s.name}: Input socket of size {s.n_elmts/slf.module.n_frames}\n"
            inputs.append(s)
        elif s.direction == Socket.directions.OUT:
            str += f"\t{s.name}: Output socket of size {s.n_elmts/slf.module.n_frames}\n"
            outputs.append(s)
        else:
            str += f"\t{s.name}: Forward socket of size {s.n_elmts/slf.module.n_frames}\n"
            inputs.append(s)
            #outputs.append(s)

    ___call___.__doc__ = str

    for i in range(len(args)):
        inputs[i].reset()
        inputs[i].bind(args[i])

    for k,s in kwargs.items():
        slf[k].reset()
        slf[k].bind(s)

    slf.exec()

    for s_out in outputs:
        s_out.__mdl__ = slf.module

    rv = tuple([s for s in outputs if s.name != "status"])
    if len(rv) > 1:
        return rv
    elif len(rv) == 1:
        return rv[0]
    else:
        return None

Task.__call__ = ___call___

__all__ = ["Task"]