# encoding: utf-8
"""Provides some array factories."""

from __future__ import annotations

from typing import Union

import numpy as np

from . import _ext


def array(
        in_array: Union[list, np.ndarray],
        n_frames: int = 1,
        dtype: _ext.dtype = None
        ) -> _ext.core.Socket:
    """Build a socket either from a numpy.array or a list.

    Args:
        in_array (list|np.ndarray): initial numpy array or list
        n_frames (int): number of frames
        dtype (dtype): socket data type

    Returns:
        out (Socket): a socket containing the same data as in object
    """
    if isinstance(in_array, (int, float)):
        in_array = [in_array]

    if isinstance(in_array, list) and not dtype:
        dtype = _ext.float64
        if all(isinstance(x, int) for x in in_array):
            dtype = _ext.int64

    elif isinstance(in_array, np.ndarray) and not dtype:
        dtype = getattr(_ext, in_array.dtype.type.__name__)

    lst = np.array(in_array, dtype=np.dtype(dtype.name))
    attr_name = f'Array_{dtype.name}'
    if lst.size == 1:
        mdl = getattr(_ext.arr, attr_name)(1, lst)
    else:
        mdl = getattr(_ext.arr, attr_name)(lst)
    if n_frames > 1:
        mdl.n_frames = n_frames
    return mdl.get()


def zeros(
        n_elmts: int = 1,
        n_frames: int = 1,
        dtype: _ext.dtype = _ext.float32
        ) -> _ext.core.Socket:
    """Build a socket filled with zeros.

    Args:
        n_elmts (int): socket number of elements
        n_frames (int): number of frames
        dtype (dtype): socket data type

    Returns:
        out (Socket): a socket filled with 0
    """
    mdl = getattr(_ext.arr, f'Array_{dtype.name}')(n_elmts, 0)
    if n_frames > 1:
        mdl.n_frames = n_frames
    return mdl.get()


def ones(
        n_elmts: int = 1,
        n_frames: int = 1,
        dtype: _ext.dtype = _ext.float32
        ) -> _ext.core.Socket:
    """Build a socket filled with ones.

    Args:
        n_elmts (int): socket number of elements
        n_frames (int): number of frames
        dtype (dtype): socket data type

    Returns:
        out (Socket): a socket filled with 1
    """
    mdl = getattr(_ext.arr, f'Array_{dtype.name}')(n_elmts, 1)
    if n_frames > 1:
        mdl.n_frames = n_frames
    return mdl.get()


def arange(
        start: Union[int, float],
        stop: Union[int, float],
        step: Union[int, float] = 1,
        n_frames: int = 1,
        dtype: _ext.dtype = _ext.float32
        ) -> _ext.core.Socket:
    """Build a socket similar to np.arange.

    Args:
        start (int|float): start of the interval
        stop (int|float): end of the interval
        step (int|float): step
        n_frames (int): number of frames
        dtype (dtype): socket data type

    Returns:
        out (Socket): a socket of evenly spaced values.
    """
    arr = np.arange(start, stop, step, dtype=np.dtype(dtype.name))
    return array(arr, n_frames, dtype)


__all__ = ['array', 'zeros', 'ones', 'arange']
