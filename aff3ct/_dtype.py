from aff3ct._ext import dtype, uint8, uint16, uint32, uint64, int8, int16, int32, int64, float32, float64
from aff3ct._ext.core import Socket
from ._array import array

def __dtype_call__(slf, data):
    if type(data) is Socket:
        return data.astype(slf)
    else:
        return array(data, dtype = slf)

dtype.__call__ = lambda slf, data: __dtype_call__(slf, data)

__all__ = ['dtype', 'uint8', 'uint16', 'uint32', 'uint64', 'int8', 'int16',
           'int32', 'int64', 'float32', 'float64']