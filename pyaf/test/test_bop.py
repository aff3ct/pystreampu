import pyaf
import numpy as np

def test_bop_add(dtype):
    x = np.array(12.6,dtype=dtype.numpy)
    y = np.array(13.2,dtype=dtype.numpy)
    z = x+y

    px = pyaf.array(x)
    py = pyaf.array(y)
    pz = px + py
    assert(np.allclose(pz,z))

def test_bop_sub(signed_dtype):
    x = np.array(12.6,dtype=signed_dtype.numpy)
    y = np.array(13.2,dtype=signed_dtype.numpy)
    z = x-y

    px = pyaf.array(x)
    py = pyaf.array(y)
    pz = px - py
    assert(np.allclose(pz,z))

def test_bop_mul(dtype):
    x = np.array(12.6,dtype=dtype.numpy)
    y = np.array(13.2,dtype=dtype.numpy)
    z = x * y

    px = pyaf.array(x)
    py = pyaf.array(y)
    pz = px * py
    assert(np.allclose(pz,z))

def test_bop_div(float_dtype):
    x = np.array(12.6,dtype=float_dtype.numpy)
    y = np.array(13.2,dtype=float_dtype.numpy)
    z = x / y

    px = pyaf.array(x)
    py = pyaf.array(y)
    pz = px / py
    assert(np.allclose(pz,z))

def test_bop_div2(int_dtype):
    x = np.array(12,dtype=int_dtype.numpy)
    y = np.array(2,dtype=int_dtype.numpy)
    z = x // y

    px = pyaf.array(x)
    py = pyaf.array(y)
    pz = px / py
    assert(np.allclose(pz,z))