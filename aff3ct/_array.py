"""Provides some array factories."""
from __future__ import annotations

from typing import List, Union

from ._typing import SocketLike

import numpy as np

from . import _ext

def array(
    value: Union[float, List, List[list], np.array],
    size: int = 1,
    n_frames: int = 1,
    dtype: _ext.dtype = None
) -> _ext.core.Socket:

    # Ensures dtype is defined
    if not dtype and not isinstance(value, np.ndarray):
        dtype = _ext.float64
    elif not dtype and isinstance(value, np.ndarray):
        dtype = value.dtype

    # get module's name
    attr_name = f'Array_{dtype.name}'

    # convert np.array to list
    if isinstance(value, np.ndarray):
        value = value.tolist()

    # list of list
    if all(isinstance(elem, list) for elem in value):
        return getattr(_ext.arr, attr_name)(value).get()

    # list
    if isinstance(value, list):
        return getattr(_ext.arr, attr_name)([value]*n_frames).get()

    # scalar
    if isinstance(value, float):
        return getattr(_ext.arr, attr_name)([[value*size]]*n_frames).get()

    err_msg = f'Cannot convert type {type(value)} into an AFF3CT Socket.'
    raise NotImplementedError(err_msg)


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

           x = aff3ct.zeros(8, dtype=aff3ct.int16)
           print(x)

           [0 0 0 0 0 0 0 0]

    See Also:
        :meth:`aff3ct.array`, :meth:`aff3ct.ones`, :meth:`aff3ct.arange`
    """
    mdl = getattr(_ext.arr, f'Array_{dtype.name}')(n_elmts, 0)
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
        >>> x = aff3ct.ones(8)
        >>> x
        socket([1. 1. 1. 1. 1. 1. 1. 1.], dtype=float32, name=X, task=Array.get)
        >>> x = aff3ct.ones(8, dtype=aff3ct.int16)
        >>> x
        socket([1 1 1 1 1 1 1 1], dtype=int16, name=X, task=Array.get)

    See Also:
        :meth:`aff3ct.array`, :meth:`aff3ct.zeros`, :meth:`aff3ct.arange`
    """
    mdl = getattr(_ext.arr, f'Array_{dtype.name}')(n_elmts, 1)
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
        >>> x = aff3ct.arange(1, 2, 0.25, dtype=aff3ct.float64)
        >>> x
        socket([1.   1.25 1.5  1.75], dtype=float64, name=X,task=Array.get)

    See Also:
        :meth:`aff3ct.array`, :meth:`aff3ct.zeros`, :meth:`aff3ct.ones`
    """
    arr = np.arange(start, stop, step, dtype=np.dtype(dtype.name))
    return array(arr, n_frames, dtype)


__all__ = ['array', 'zeros', 'ones', 'arange']
