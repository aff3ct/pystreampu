import numpy as np
from ..builtins.core import Socket
from ..builtins import Slicer
from .. import array

def __socket_repr__(sck):
    data_str = np.array(sck).__str__()
    str = f"socket({data_str}, dtype={sck.dtype.name}, name={sck.name}, task={sck.task.module.name}.{sck.task.name})"
    return str

Socket.__str__  = lambda s : np.array(s).__str__()
Socket.__repr__ = lambda s : __socket_repr__(s)
Socket.__len__  = lambda s : np.array(s).__len__()

def __from_array__(s, dtype = None, n_frames = 1):
    try:
        arr = None
        if dtype:
            arr = np.array(s, dtype = np.dtype(dtype.name)) # Convert
        else:
            arr = np.array(s) # Convert
        so = array.array.array(arr, n_frames=n_frames)#.dtype.name
        so.task()
        so.__mdl__ = so.task.module
    except Exception as inst:
        return NotImplemented # TODO : Error message

    return so

Socket.from_array = lambda s , dtype = None, n_frames = 1: __from_array__(s, dtype, n_frames)

def ___bind___(slf, s_out, priority=1):
    # The __tag__ attribute of module will store the modules which are binded to mdl
    mdl = slf.task.module
    if not hasattr(mdl, "__tag__"):
        mdl.__tag__ = dict.fromkeys([tsk.name for tsk in mdl.tasks], {})

    if type(s_out) is not Socket:
        s_out = __from_array__(s_out)
    else:
        while hasattr(s_out, "__mrv__"):
            s_out = s_out.__mrv__

    mdl.__tag__[slf.task.name][slf.name] = s_out

    if slf.direction == Socket.directions.FWD:
        # If slf is a forward socket, then it will be the most recent value of s_out
        s_out.__mrv__ = slf

    slf.__bind__(s_out, priority)

Socket.bind = lambda slf, s_out, priority=1:___bind___(slf, s_out, priority)

def ___setitem___(slf, key, data):
    slc = None
    if type(key) is slice:
        start, stop, step = key.indices(slf.n_elmts // slf.task.module.n_frames)
        slc = Slicer(slf, np.arange(start, stop, step))
    elif type(key) is int:
        slc = Slicer(slf, key)

    slc.n_frames = slf.task.module.n_frames
    if hasattr(data,"__len__") and len(data) > 1:
        slc.write(slf, data)
    else:
        slc.write_one(slf, data)

    #TODO : fix this
    if not hasattr(slf, "__slicers__"):
        slf.__slicers__ = []
    slf.__slicers__.append(slc)

def ___getitem___(slf, key):
    slc = None
    if type(key) is slice:
        start, stop, step = key.indices(slf.n_elmts // slf.task.module.n_frames)
        slc = Slicer(slf, np.arange(start, stop, step))
    elif type(key) is int:
        slc = Slicer(slf, key)

    slc.n_frames = slf.task.module.n_frames

    #TODO : fix this
    if not hasattr(slf, "__slicers__"):
        slf.__slicers__ = []
    slf.__slicers__.append(slc)

    return slc.read(slf)

Socket.__setitem__ = lambda s, k, d: ___setitem___(s,k,d)
Socket.__getitem__ = lambda s, k   : ___getitem___(s,k)

__all__ = ["Socket"]