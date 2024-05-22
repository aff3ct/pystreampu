import streampu._ext
from streampu._ext import int32


def incrementer(n_elmts: int, ns: int = 0, dtype: streampu._ext.dtype = int32):
    if not isinstance(dtype, streampu._ext.dtype):
        msg = f"type '{type(dtype)}' does not name an StreamPU datatype."
        raise TypeError(msg)
    class_name = f"Incrementer_{str(dtype)}"
    class_type = getattr(streampu._ext.inc, class_name)
    return class_type(n_elmts, ns)


__all__ = ["incrementer"]
