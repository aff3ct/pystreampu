import streampu._ext
from streampu._ext import int32


def finalizer(n_elmts: int, dtype: streampu._ext.dtype = int32):
    if not isinstance(dtype, streampu._ext.dtype):
        msg = f"type '{type(dtype)}' does not name an StreamPU datatype."
        raise TypeError(msg)
    class_name = f"Finalizer_{str(dtype)}"
    class_type = getattr(streampu._ext.fin, class_name)
    return class_type(n_elmts)


__all__ = ["finalizer"]
