# -*- coding: utf-8 -*-
"""Functionnal tests for binary operators."""
import numpy as np

from streampu import array


def test_bop_add(dtype):
    """Test 'add' binary operator.

    Args:
        dtype (streampu._ext.dtype): Data type
    """
    x = np.array([12.6], dtype=dtype.numpy)
    y = np.array([13.2], dtype=dtype.numpy)
    z = x + y

    px = array(x)
    py = array(y)
    pz = px + py
    assert np.allclose(pz.numpy, z)


def test_bop_sub(signed_dtype):
    """Test 'sub' binary operator.

    Args:
        signed_dtype (streampu._ext.dtype): Signed data type
    """
    x = np.array([12.6], dtype=signed_dtype.numpy)
    y = np.array([13.2], dtype=signed_dtype.numpy)
    z = x - y

    px = array(x)
    py = array(y)
    pz = px - py
    assert np.allclose(pz.numpy, z)


def test_bop_mul(dtype):
    """Test 'mul' binary operator.

    Args:
        dtype (streampu._ext.dtype): Data type
    """
    x = np.array([12.6], dtype=dtype.numpy)
    y = np.array([13.2], dtype=dtype.numpy)
    z = x * y

    px = array(x)
    py = array(y)
    pz = px * py
    assert np.allclose(pz.numpy, z)


def test_bop_div(float_dtype):
    """Test 'div' binary operator.

    Args:
        float_dtype (streampu._ext.dtype): Float data type
    """
    x = np.array([12.6], dtype=float_dtype.numpy)
    y = np.array([13.2], dtype=float_dtype.numpy)
    z = x / y

    px = array(x)
    py = array(y)
    pz = px / py
    assert np.allclose(pz.numpy, z)


def test_bop_div2(int_dtype):
    """Test 'div2' binary operator.

    Args:
        int_dtype (streampu._ext.dtype): Integer data type
    """
    x = np.array([12], dtype=int_dtype.numpy)
    y = np.array([2], dtype=int_dtype.numpy)
    z = x // y

    px = array(x)
    py = array(y)
    pz = px / py
    assert np.allclose(pz.numpy, z)


def test_bop_gt(float_dtype):
    """Test 'gt' binary operator.

    Args:
        float_dtype (streampu._ext.dtype): Float data type
    """
    x = np.array([12.6], dtype=float_dtype.numpy)
    y = np.array([13.2], dtype=float_dtype.numpy)
    z = x > y

    px = array(x)
    py = array(y)
    pz = px > py
    assert np.allclose(pz.numpy, z)


def test_bop_lt(float_dtype):
    """Test 'lt' binary operator.

    Args:
        float_dtype (streampu._ext.dtype): Float Data type
    """
    x = np.array([12.6], dtype=float_dtype.numpy)
    y = np.array([13.2], dtype=float_dtype.numpy)
    z = x < y

    px = array(x)
    py = array(y)
    pz = px < py
    assert np.allclose(pz.numpy, z)


def test_bop_ge(float_dtype):
    """Test 'ge' binary operator.

    Args:
        float_dtype (streampu._ext.dtype): Float data type
    """
    x = np.array([12.6], dtype=float_dtype.numpy)
    y = np.array([13.2], dtype=float_dtype.numpy)
    z = x >= y

    px = array(x)
    py = array(y)
    pz = px >= py
    assert np.allclose(pz.numpy, z)


def test_bop_le(float_dtype):
    """Test 'le' binary operator.

    Args:
        float_dtype (streampu._ext.dtype): Float data type
    """
    x = np.array([12.6], dtype=float_dtype.numpy)
    y = np.array([13.2], dtype=float_dtype.numpy)
    z = x <= y

    px = array(x)
    py = array(y)
    pz = px <= py
    assert np.allclose(pz.numpy, z)


def test_bop_eq(float_dtype):
    """Test 'eq' binary operator.

    Args:
        float_dtype (streampu._ext.dtype): float data type
    """
    x = np.array([12.6], dtype=float_dtype.numpy)
    y = np.array([13.2], dtype=float_dtype.numpy)
    z = x == y

    px = array(x)
    py = array(y)
    pz = px == py
    assert np.allclose(pz.numpy, z)


def test_bop_neq(float_dtype):
    """Test 'neq' binary operator.

    Args:
        float_dtype (streampu._ext.dtype): Float data type
    """
    x = np.array([12.6], dtype=float_dtype.numpy)
    y = np.array([13.2], dtype=float_dtype.numpy)
    z = x != y

    px = array(x)
    py = array(y)
    pz = px != py

    assert np.allclose(pz.numpy, z)


def test_bop_add_const(dtype):
    """Test 'add' binary operator with constant.

    Args:
        dtype (streampu._ext.dtype): Data type
    """
    x = np.array([12.6], dtype=dtype.numpy)
    y = dtype.numpy([13.2])
    z = x + y

    px = array(x)
    pz = px + y
    assert np.allclose(pz.numpy, z)


def test_bop_sub_const(signed_dtype):
    """Test 'sub' binary operator with constant.

    Args:
        signed_dtype (streampu._ext.dtype): Signed data type
    """
    x = np.array([12.6], dtype=signed_dtype.numpy)
    y = signed_dtype.numpy([13.2])
    z = x - y

    px = array(x)
    pz = px - y
    assert np.allclose(pz.numpy, z)


def test_bop_mul_const(dtype):
    """Test 'mul' binary operator with constant.

    Args:
        dtype (streampu._ext.dtype): Data type
    """
    x = np.array([12.6], dtype=dtype.numpy)
    y = dtype.numpy([13.2])
    z = x * y

    px = array(x)
    pz = px * y
    assert np.allclose(pz.numpy, z)
