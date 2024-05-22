import aff3ct._ext
from aff3ct._ext import int16


def source(max_data_size: int, dtype: aff3ct._ext.dtype = int16):
    if not isinstance(dtype, aff3ct._ext.dtype):
        msg = f"type '{type(dtype)}' does not name an AFF3CT datatype."
        raise TypeError(msg)
    class_name = f"Source_{str(dtype)}"
    class_type = getattr(aff3ct._ext.src, class_name)
    return class_type(max_data_size)


def source_random(max_data_size: int, seed: int = 0, dtype: aff3ct._ext.dtype = int16):
    if not isinstance(dtype, aff3ct._ext.dtype):
        msg = f"type '{type(dtype)}' does not name an AFF3CT datatype."
        raise TypeError(msg)
    class_name = f"Source_random_{str(dtype)}"
    class_type = getattr(aff3ct._ext.src, class_name)
    return class_type(max_data_size, seed)


def source_user_binary(
    max_data_size: int,
    filename: str,
    auto_reset: bool = True,
    fifo_mode: bool = False,
    dtype: aff3ct._ext.dtype = int16,
):
    if not isinstance(dtype, aff3ct._ext.dtype):
        msg = f"type '{type(dtype)}' does not name an AFF3CT datatype."
        raise TypeError(msg)
    class_name = f"Source_user_binary_{str(dtype)}"
    class_type = getattr(aff3ct._ext.src, class_name)
    return class_type(max_data_size, filename, auto_reset, fifo_mode)


def source_user(
    max_data_size: int,
    filename: str,
    auto_reset: bool = True,
    start_idx: int = 0,
    dtype: aff3ct._ext.dtype = int16,
):
    if not isinstance(dtype, aff3ct._ext.dtype):
        msg = f"type '{type(dtype)}' does not name an AFF3CT datatype."
        raise TypeError(msg)
    class_name = f"Source_user_{str(dtype)}"
    class_type = getattr(aff3ct._ext.src, class_name)
    return class_type(max_data_size, filename, auto_reset, start_idx)


__all__ = ["source", "source_random", "source_user_binary", "source_user"]
