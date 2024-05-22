import streampu._ext
from streampu._ext import int32


def relayer(n_elmts: int, ns: int = 0, dtype: streampu._ext.dtype = int32):
    if not isinstance(dtype, streampu._ext.dtype):
        msg = f"type '{type(dtype)}' does not name an StreamPU datatype."
        raise TypeError(msg)
    class_name = f"Relayer_{str(dtype)}"
    class_type = getattr(streampu._ext.rel, class_name)
    return class_type(n_elmts, ns)


__all__ = ["relayer"]
