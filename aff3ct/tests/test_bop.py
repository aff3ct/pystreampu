from aff3ct import array
import numpy as np


def test_bop_add(dtype):
    x = np.array([12.6], dtype=dtype.numpy)
    y = np.array([13.2], dtype=dtype.numpy)
    z = x + y

    px = array(x)
    py = array(y)
    pz = px + py
    assert np.allclose(pz.numpy, z)


def test_bop_sub(signed_dtype):
    x = np.array([12.6], dtype=signed_dtype.numpy)
    y = np.array([13.2], dtype=signed_dtype.numpy)
    z = x - y

    px = array(x)
    py = array(y)
    pz = px - py
    assert np.allclose(pz.numpy, z)


def test_bop_mul(dtype):
    x = np.array([12.6], dtype=dtype.numpy)
    y = np.array([13.2], dtype=dtype.numpy)
    z = x * y

    px = array(x)
    py = array(y)
    pz = px * py
    assert np.allclose(pz.numpy, z)


def test_bop_div(float_dtype):
    x = np.array([12.6], dtype=float_dtype.numpy)
    y = np.array([13.2], dtype=float_dtype.numpy)
    z = x / y

    px = array(x)
    py = array(y)
    pz = px / py
    assert np.allclose(pz.numpy, z)


def test_bop_div2(int_dtype):
    x = np.array([12], dtype=int_dtype.numpy)
    y = np.array([2], dtype=int_dtype.numpy)
    z = x // y

    px = array(x)
    py = array(y)
    pz = px / py
    assert np.allclose(pz.numpy, z)


def test_bop_gt(float_dtype):
    x = np.array([12.6], dtype=float_dtype.numpy)
    y = np.array([13.2], dtype=float_dtype.numpy)
    z = x > y

    px = array(x)
    py = array(y)
    pz = px > py
    assert np.allclose(pz.numpy, z)


def test_bop_lt(float_dtype):
    x = np.array([12.6], dtype=float_dtype.numpy)
    y = np.array([13.2], dtype=float_dtype.numpy)
    z = x < y

    px = array(x)
    py = array(y)
    pz = px < py
    assert np.allclose(pz.numpy, z)


def test_bop_ge(float_dtype):
    x = np.array([12.6], dtype=float_dtype.numpy)
    y = np.array([13.2], dtype=float_dtype.numpy)
    z = x >= y

    px = array(x)
    py = array(y)
    pz = px >= py
    assert np.allclose(pz.numpy, z)


def test_bop_le(float_dtype):
    x = np.array([12.6], dtype=float_dtype.numpy)
    y = np.array([13.2], dtype=float_dtype.numpy)
    z = x <= y

    px = array(x)
    py = array(y)
    pz = px <= py
    assert np.allclose(pz.numpy, z)


def test_bop_eq(float_dtype):
    x = np.array([12.6], dtype=float_dtype.numpy)
    y = np.array([13.2], dtype=float_dtype.numpy)
    z = x == y

    px = array(x)
    py = array(y)
    pz = px == py
    assert np.allclose(pz.numpy, z)


def test_bop_neq(float_dtype):
    x = np.array([12.6], dtype=float_dtype.numpy)
    y = np.array([13.2], dtype=float_dtype.numpy)
    z = x != y

    px = array(x)
    py = array(y)
    pz = px != py

    assert np.allclose(pz.numpy, z)


def test_bop_add_const(dtype):
    x = np.array([12.6], dtype=dtype.numpy)
    y = dtype.numpy([13.2])
    z = x + y

    px = array(x)
    pz = px + y
    assert np.allclose(pz.numpy, z)


def test_bop_sub_const(signed_dtype):
    x = np.array([12.6], dtype=signed_dtype.numpy)
    y = signed_dtype.numpy([13.2])
    z = x - y

    px = array(x)
    pz = px - y
    assert np.allclose(pz.numpy, z)


def test_bop_mul_const(dtype):
    x = np.array([12.6], dtype=dtype.numpy)
    y = dtype.numpy([13.2])
    z = x * y

    px = array(x)
    pz = px * y
    assert np.allclose(pz.numpy, z)
