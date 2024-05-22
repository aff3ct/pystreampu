import aff3ct._ext
from aff3ct._ext import int32


def finalizer(n_elmts: int, dtype: aff3ct._ext.dtype = int32):
    if not isinstance(dtype, aff3ct._ext.dtype):
        msg = f"type '{type(dtype)}' does not name an AFF3CT datatype."
        raise TypeError(msg)
    class_name = f"Finalizer_{str(dtype)}"
    class_type = getattr(aff3ct._ext.fin, class_name)
    return class_type(n_elmts)


__all__ = ["finalizer"]
