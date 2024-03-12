import aff3ct._ext
from aff3ct._ext import int32


def incrementer(n_elmts: int,
                ns: int = 0,
                dtype: aff3ct._ext.dtype = int32):
    if not isinstance(dtype, aff3ct._ext.dtype):
        msg = f"type '{type(dtype)}' does not name an AFF3CT datatype."
        raise TypeError(msg)
    class_name = f'Incrementer_{str(dtype)}'
    class_type = getattr(aff3ct._ext.inc, class_name)
    return class_type(n_elmts, ns)


__all__ = ['incrementer']
