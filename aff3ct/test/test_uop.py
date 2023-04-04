from ..array.array import array
import numpy as np
import pytest

from .conftest import list_types

def test_uop_neg(signed_dtype):
    x = np.array(12.6,dtype=signed_dtype.numpy)
    z = -x

    px = array(x)
    pz = -px
    assert(np.allclose(pz,z))

def test_uop_not(int_dtype):
    x = np.array(12,dtype=int_dtype.numpy)
    z = ~x

    px = array(x)
    pz = ~px
    assert(np.allclose(pz,z))

@pytest.mark.parametrize('TI', list_types)
@pytest.mark.parametrize('TO', list_types)
def test_uop_cast(TI, TO):
    x = np.array(12,dtype=TI.numpy)
    z = x.astype(TO.numpy)

    px = array(x)
    pz = px.astype(TO)
    assert(np.allclose(pz,z))