from aff3ct import (uint8, uint16, uint32, uint64, int8,
                    int16, int32, int64, float32, float64)

list_types = [uint8, uint16, uint32, uint64, int8, int16, int32, int64,
              float32, float64]

def pytest_generate_tests(metafunc):

    if "dtype" in metafunc.fixturenames:
        lt  = list_types
        metafunc.parametrize("dtype", lt, ids=[t.name for t in lt])

    if "signed_dtype" in metafunc.fixturenames:
        lt = [t for t in list_types if t.is_signed]
        metafunc.parametrize("signed_dtype", lt, ids=[t.name for t in lt])

    if "float_dtype" in metafunc.fixturenames:
        lt = [t for t in list_types if t.is_floating_point]
        metafunc.parametrize("float_dtype", lt, ids=[t.name for t in lt])

    if "int_dtype" in metafunc.fixturenames:
        lt = [t for t in list_types if not t.is_floating_point]
        metafunc.parametrize("int_dtype", lt, ids=[t.name for t in lt])

