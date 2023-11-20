from aff3ct import array, arange
import numpy as np

def test_array_type(dtype):
    x = array([1, 2, 3, 4], 14, dtype = dtype)
    assert (x.dtype.name == dtype.name)

def test_array_value(dtype):
    x = array([25], 14, dtype=dtype)
    assert (x.numpy[0] == dtype.numpy(25))

def test_array_size(dtype):
    x = array([25], 14, dtype = dtype)
    assert (x.n_elmts == 14)

def test_arange(dtype):
    x  = np.arange(0, 255, 2.3, dtype = dtype.numpy)
    px = arange(0, 255, 2.3, dtype = dtype)

    assert (np.allclose(px.numpy[:], x[:]))
