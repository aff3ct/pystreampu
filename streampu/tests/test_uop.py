# -*- coding: utf-8 -*-
"""Functionnal tests for unary operators."""

import numpy as np
import pytest

from streampu import array

from .conftest import list_types


def test_uop_neg(signed_dtype):
    """Test 'neg' unary operator.

    Args:
        signed_dtype (streampu._ext.dtype): Signed data type
    """
    x = np.array([12.6], dtype=signed_dtype.numpy)
    z = -x

    px = array(x)
    pz = -px
    assert np.allclose(pz.numpy, z)


def test_uop_not(int_dtype):
    """Test 'not' unary operator.

    Args:
        int_dtype (streampu._ext.dtype): Integer data type
    """
    x = np.array([12], dtype=int_dtype.numpy)
    z = ~x

    px = array(x)
    pz = ~px
    assert np.allclose(pz.numpy, z)


@pytest.mark.parametrize("input_dtype", list_types)
@pytest.mark.parametrize("output_dtype", list_types)
def test_uop_cast(input_dtype, output_dtype):
    """Test 'cast' unary operator.

    Args:
        input_dtype (streampu._ext.dtype): Input data type
        output_dtype (streampu._ext.dtype): Output data type
    """
    x = np.array([12], dtype=input_dtype.numpy)
    z = x.astype(output_dtype.numpy)

    px = array(x)
    pz = px.astype(output_dtype)
    assert np.allclose(pz.numpy, z)
