"""Provides some array factories."""
from __future__ import annotations

from ._typing import SocketLike

import numpy as np

from . import _ext


def _find_common_type(lst: list) -> _ext.dtype:
    """Return the common type of a list.

    Args:
        lst (list): input list

    Returns:
        out (dtype): a common dtype for the list
    """
    dtype = _ext.float64
    if all(isinstance(x, int) for x in lst):
        dtype = _ext.int64
    return dtype


def array(
    in_array: SocketLike,
    n_frames: int = 1,
    dtype: _ext.dtype = None
) -> _ext.core.Socket:
    """Build a socket either from a numpy.array or a list.

    Args:
        in_array (SocketLike): initial numpy array or list.
        n_frames (int): number of frames.
        dtype (dtype): socket data type.

    Returns:
        Socket: a socket containing the same data as in object.

    Examples:

        If all elements in the list are int and no dtype, the dtype of x will
        be int64

        >>> x = aff3ct.array([1,2,3,4,5])
        >>> x
        socket([1 2 3 4 5], dtype=int64, name=X, task=Array.get)

        If one (or more) element is a float and no dtype, the dtype of x will
        be float64

        >>> x = aff3ct.array([1.0,2,3,4,5])
        >>> x

        If a dtype is set, x will have this dtype
        socket([1. 2. 3. 4. 5.], dtype=float64, name=X, task=Array.get)

        >>> x = aff3ct.array([1.0,2,3,4,5], dtype=aff3ct.int8)
        >>> x
        socket([1 2 3 4 5], dtype=int8, name=X, task=Array.get)

    See Also:
        :meth:`aff3ct.ones`, :meth:`aff3ct.zeros`, :meth:`aff3ct.arange`

    """
    if isinstance(in_array, _ext.core.Socket):
        return in_array

    if isinstance(in_array, (int, float)):
        in_array = [in_array]

    if isinstance(in_array, list) and not dtype:
        dtype = _find_common_type(in_array)
    elif isinstance(in_array, np.ndarray) and not dtype:
        dtype = getattr(_ext, in_array.dtype.type.__name__)

    lst = np.array(in_array, dtype=np.dtype(dtype.name))
    attr_name = f'Array_{dtype.name}'

    if lst.size == 1:
        mdl = getattr(_ext.arr, attr_name)(1, lst[0])
    else:
        mdl = getattr(_ext.arr, attr_name)(lst)

    mdl.n_frames = n_frames
    return mdl.get()


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
