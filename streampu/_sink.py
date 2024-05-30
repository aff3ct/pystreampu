# -*- coding: utf-8 -*-
import streampu._ext
from streampu._ext import int16


def sink_no(max_data_size: int, dtype: streampu._ext.dtype = int16):
    """Build a new Sink_NO.

    Args:
        max_data_size (int): input data size
        dtype (streampu._ext.dtype): Data type

    Returns:
        out (Module): a new sink

    Raises:
        TypeError: if dtype is not a valid dtype
    """
    if not isinstance(dtype, streampu._ext.dtype):
        msg = f"type '{type(dtype)}' does not name an StreamPU datatype."
        raise TypeError(msg)
    class_name = f"Sink_NO_{str(dtype)}"
    class_type = getattr(streampu._ext.snk, class_name)
    return class_type(max_data_size)


def sink_user_binary(max_data_size: int, filename: str, dtype: streampu._ext.dtype = int16):
    """Build a new Sink_user_binary.

    Args:
        max_data_size (int): input data size
        filename (str): File name
        dtype (streampu._ext.dtype): Data type

    Returns:
        out (Module): a new sink

    Raises:
        TypeError: if dtype is not a valid dtype
    """
    if not isinstance(dtype, streampu._ext.dtype):
        msg = f"type '{type(dtype)}' does not name an StreamPU datatype."
        raise TypeError(msg)
    class_name = f"Sink_user_binary_{str(dtype)}"
    class_type = getattr(streampu._ext.snk, class_name)
    return class_type(max_data_size, filename)


__all__ = ["sink_user_binary", "sink_no"]
