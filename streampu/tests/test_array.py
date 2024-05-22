from streampu import array, arange
import numpy as np


def test_array_type(dtype):
    X = np.array([[1, 2, 3, 4]] * 14, dtype=dtype.numpy)
    x = array(X)
    assert x.dtype.name == dtype.name


def test_array_value(dtype):
    X = np.array([[25]] * 14, dtype=dtype.numpy)
    x = array(X)
    assert x.numpy[0, 0] == dtype.numpy(25)


def test_array_size(dtype):
    X = np.array([[25] * 10] * 14, dtype=dtype.numpy)
    x = array(X)
    assert x.n_elmts == 10 * 14


def test_arange(dtype):
    x = np.arange(0, 255, 2.3, dtype=dtype.numpy)
    px = arange(0, 255, 2.3, dtype=dtype)

    assert np.allclose(px.numpy[:], x[:])
