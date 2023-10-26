from . import _ext
import numpy as np
from typing import Union

def array(arr:Union[list, np.ndarray], n_frames:int = 1, dtype:_ext.dtype = None):
    if type(arr) is int   : arr = [arr]
    if type(arr) is float : arr = [arr]
    if type(arr) is list and not dtype:
        if all(isinstance(x, int) for x in arr):
            dtype = _ext.int64
        else:
            dtype = _ext.float64
    elif type(arr) is np.ndarray and not dtype:
        dtype = getattr(_ext, arr.dtype.type.__name__)

    lst = np.array(arr, dtype = np.dtype(dtype.name))
    if lst.size == 1:
        mdl = getattr(_ext.arr, "Array_" + dtype.name)(1,lst)
    else:
        mdl = getattr(_ext.arr, "Array_" + dtype.name)(lst)
    if n_frames > 1: mdl.n_frames = n_frames
    return mdl.get()

def zeros(n_elmts:int=1, n_frames:int=1, dtype:_ext.dtype=_ext.float32):
    mdl = getattr(_ext.arr, "Array_" + dtype.name)(n_elmts, 0)
    if n_frames > 1: mdl.n_frames = n_frames
    return mdl.get()

def ones(n_elmts:int=1, n_frames:int=1, dtype:_ext.dtype=_ext.float32):
    mdl = getattr(_ext.arr, "Array_" + dtype.name)(n_elmts, 1)
    if n_frames > 1: mdl.n_frames = n_frames
    return mdl.get()

def arange(start, stop, step=1, n_frames=1, dtype=_ext.float32):
    arr = np.arange(start, stop, step, dtype=np.dtype(dtype.name))
    return array(arr, n_frames, dtype)

__all__ = ["array", "zeros", "ones", "arange"]