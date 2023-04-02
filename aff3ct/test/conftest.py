import aff3ct

list_types = [aff3ct.uint8,aff3ct.uint16,aff3ct.uint32,aff3ct.uint64,aff3ct.int8,aff3ct.int16,aff3ct.int32,aff3ct.int64,aff3ct.float32,aff3ct.float64]

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
