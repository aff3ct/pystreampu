from .. import builtins
import numpy as np
from typing import Union

def array(arr:Union[list, np.ndarray], n_frames:int = 1, dtype:builtins.dtype = None):
    if type(arr) is list and not dtype:
        if all(isinstance(x, int) for x in arr):
            dtype = builtins.int64
        else:
            dtype = builtins.float64
    elif type(arr) is np.ndarray and not dtype:
        dtype = getattr(builtins, arr.dtype.type.__name__)

    lst = np.array(arr, dtype = np.dtype(dtype.name))
    if lst.size == 1:
        mdl = getattr(builtins.arr, "Array_" + dtype.name)(1,lst)
    else:
        mdl = getattr(builtins.arr, "Array_" + dtype.name)(lst)
    if n_frames > 1: mdl.n_frames = n_frames
    return mdl.get()

def zeros(n_elmts:int=1, n_frames:int=1, dtype:builtins.dtype=builtins.float32):
    mdl = getattr(builtins.arr, "Array_" + dtype.name)(n_elmts, 0)
    if n_frames > 1: mdl.n_frames = n_frames
    return mdl.get()

def ones(n_elmts:int=1, n_frames:int=1, dtype:builtins.dtype=builtins.float32):
    mdl = getattr(builtins.arr, "Array_" + dtype.name)(n_elmts, 1)
    if n_frames > 1: mdl.n_frames = n_frames
    return mdl.get()

def arange(start, stop, step=1, n_frames=1, dtype=builtins.float32):
    arr = np.arange(start, stop, step, dtype=np.dtype(dtype.name))
    return array(arr, n_frames, dtype)

__all__ = ["array", "zeros", "ones", "arange"]