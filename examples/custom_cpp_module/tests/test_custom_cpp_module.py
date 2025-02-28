import sys

sys.path.insert(0, "../build")

import my_module
import numpy as np

import streampu as spu


def test_custom_module(verbose=False):
    mdl = my_module.Adder(4)
    if verbose:
        spu.help(mdl)
    x = spu.array([1, 2, 3, 4], dtype=spu.float64)
    y = mdl.add_one(x)
    if verbose:
        print(y)
    assert np.allclose(y.numpy, x.numpy + 1)


if __name__ == "__main__":
    test_custom_module(verbose=True)
