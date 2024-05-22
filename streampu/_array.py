"""Provides some array factories."""

from __future__ import annotations

from typing import List, Union

from ._typing import SocketLike

import numpy as np

from . import _ext

from multipledispatch import dispatch

from warnings import warn


def array(data, n_frames=None, dtype=None) -> _ext.core.Socket:
    if isinstance(data, _ext.core.Socket):  # socket case : do nothing
        return data

    if isinstance(data, np.ndarray):
        if n_frames:
            warn_str = "When input 'data' is a 'np.ndarray',"
            warn_str += " parameter 'n_frames' is ignored."
            warn_str += "\nIt will be deduced from 'data'."
            warn(warn_str, stacklevel=2)
        if dtype:
            warn_str = "When input 'data' is a 'np.ndarray',"
            warn_str += " parameter 'dtype' is ignored."
            warn_str += "\nIt will be deduced from 'data'."
            warn(warn_str, stacklevel=2)
    else:
        if not n_frames:
            n_frames = 1

        if not dtype:
            dtype = _ext.float64

        if not isinstance(data, list):  # scalar case, TODO : improve this test
            data = [data]
        if not isinstance(data[0], list):
            data = [data] * n_frames
        data = np.array(data, dtype=dtype.numpy)

    attr_name = f"Array_{str(data.dtype)}"
    return getattr(_ext.arr, attr_name)(data).read.data


'''@dispatch(list, dtype=_ext.float64)
def array(
    value: list,
    dtype: _ext.dtype = _ext.float64
) -> _ext.core.Socket:
    """Doc 1"""
    attr_name = f'Array_{dtype.name}'
    return getattr(_ext.arr, attr_name)(value).get()

@dispatch(list, n_frames=int, dtype=_ext.dtype)
def array(
    value: list,
    n_frames: int = 1,
    dtype: _ext.dtype = _ext.float64
) -> _ext.core.Socket:
    """Doc 2"""
    attr_name = f'Array_{dtype.name}'
    return getattr(_ext.arr, attr_name)([value]*n_frames).get()

@dispatch(float, size=int, n_frames=int, dtype=_ext.dtype)
def array(
    value: float,
    size: int = 1,
    n_frames: int = 1,
    dtype:_ext.dtype = _ext.float64
) -> _ext.core.Socket:
    """Doc 3"""
    attr_name = f'Array_{dtype.name}'
    return getattr(_ext.arr, attr_name)([[value]*size]*n_frames).get()

@dispatch(int, size=int, n_frames=int, dtype=_ext.dtype)
def array(
    value:int,
    size:int = 1,
    n_frames:int = 1,
    dtype:_ext.dtype = _ext.float64
) -> _ext.core.Socket:
    """Doc 4"""
    attr_name = f'Array_{dtype.name}'
    return getattr(_ext.arr, attr_name)([[value]*size]*n_frames).get()
'''


def zeros(
    n_elmts: int = 1, n_frames: int = 1, dtype: _ext.dtype = _ext.float32
) -> _ext.core.Socket:
    """Build a socket filled with zeros.

    Args:
        n_elmts (int): socket number of elements
        n_frames (int): number of frames
        dtype (dtype): socket data type

    Returns:
        Socket: a socket filled with 0

    Examples:

        .. code-block:: python

           x = streampu.zeros(8, dtype=streampu.int16)
           print(x)

           [0 0 0 0 0 0 0 0]

    See Also:
        :meth:`streampu.array`, :meth:`streampu.ones`, :meth:`streampu.arange`
    """
    mdl = getattr(_ext.arr, f"Array_{dtype.name}")(n_elmts, 0)
    if n_frames > 1:
        mdl.n_frames = n_frames
    return mdl.get()


def ones(
    n_elmts: int = 1, n_frames: int = 1, dtype: _ext.dtype = _ext.float32
) -> _ext.core.Socket:
    """Build a socket filled with ones.

    Args:
        n_elmts (int): socket number of elements
        n_frames (int): number of frames
        dtype (dtype): socket data type

    Returns:
        Socket: a socket filled with 1

    Examples:
        >>> x = streampu.ones(8)
        >>> x
        socket([1. 1. 1. 1. 1. 1. 1. 1.], dtype=float32, name=X, task=Array.get)
        >>> x = streampu.ones(8, dtype=streampu.int16)
        >>> x
        socket([1 1 1 1 1 1 1 1], dtype=int16, name=X, task=Array.get)

    See Also:
        :meth:`streampu.array`, :meth:`streampu.zeros`, :meth:`streampu.arange`
    """
    mdl = getattr(_ext.arr, f"Array_{dtype.name}")(n_elmts, 1)
    if n_frames > 1:
        mdl.n_frames = n_frames
    return mdl.get()


def arange(
    start: float,
    stop: float,
    step: float = 1,
    n_frames: int = 1,
    dtype: _ext.dtype = _ext.float32,
) -> _ext.core.Socket:
    """Build a socket similar to np.arange.

    Args:
        start (float): start of the interval
        stop (float): end of the interval
        step (float): step
        n_frames (int): number of frames
        dtype (dtype): socket data type

    Returns:
        Socket: a socket of evenly spaced values.


    Examples:
        >>> x = streampu.arange(1, 2, 0.25, dtype=streampu.float64)
        >>> x
        socket([1.   1.25 1.5  1.75], dtype=float64, name=X,task=Array.get)

    See Also:
        :meth:`streampu.array`, :meth:`streampu.zeros`, :meth:`streampu.ones`
    """
    arr = np.arange(start, stop, step, dtype=np.dtype(dtype.name))
    return array(arr)


__all__ = ["array", "zeros", "ones", "arange"]
