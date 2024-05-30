# -*- coding: utf-8 -*-
"""Functionnal tests for array."""
import numpy as np

from streampu import arange, array


def test_array_type(dtype):
    """Check array type.

    Args:
        dtype (streampu._ext.dtype): Data type
    """
    npx = np.array([[1, 2, 3, 4]] * 14, dtype=dtype.numpy)
    x = array(npx)
    assert x.dtype.name == dtype.name


def test_array_value(dtype):
    """Check array value.

    Args:
        dtype (streampu._ext.dtype): Data type
    """
    npx = np.array([[25]] * 14, dtype=dtype.numpy)
    x = array(npx)
    assert x.numpy[0, 0] == dtype.numpy(25)


def test_array_size(dtype):
    """Check array size.

    Args:
        dtype (streampu._ext.dtype): Data type
    """
    npx = np.array([[25] * 10] * 14, dtype=dtype.numpy)
    x = array(npx)
    assert x.n_elmts == 10 * 14


def test_arange(dtype):
    """Check behaviour of arange.

    Args:
        dtype (streampu._ext.dtype): Data type
    """
    x = np.arange(0, 255, 2.3, dtype=dtype.numpy)
    px = arange(0, 255, 2.3, dtype=dtype)

    assert np.allclose(px.numpy[:], x[:])
