"""Add some python magic for handling dtypes."""

from __future__ import annotations

from typing import Union

import numpy as np

from . import _ext
from ._array import array

dtype = _ext.dtype
uint8 = _ext.uint8
uint16 = _ext.uint16
uint32 = _ext.uint32
uint64 = _ext.uint64
int8 = _ext.int8
int16 = _ext.int16
int32 = _ext.int32
int64 = _ext.int64
float32 = _ext.float32
float64 = _ext.float64
Socket = _ext.core.Socket


def _dtype_call(self: dtype, data: Union[Socket, np.array]) -> Socket:
    """Create socket representing `data` with the dtype of `self`.

    Args:
        self (dtype): A dtype object
        data (Socket): A socket or a numpy array to be casted.

    Returns:
        out (Socket): a socket representing data with the `dtype` of `self`
    """
    if isinstance(data, Socket):
        return data.astype(self)

    return array(data, dtype=self)


dtype.__call__ = _dtype_call

__all__ = [
    "dtype",
    "uint8",
    "uint16",
    "uint32",
    "uint64",
    "int8",
    "int16",
    "int32",
    "int64",
    "float32",
    "float64",
]
