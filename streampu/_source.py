# -*- coding: utf-8 -*-
import streampu._ext
from streampu._ext import int16


def source_random(max_data_size: int, seed: int = 0, dtype: streampu._ext.dtype = int16):
    """Build a new Source_random.

    Args:
        max_data_size (int): output data size
        seed (int): Seed for random number generation
        dtype (streampu._ext.dtype): Data type

    Returns:
        out (Module): a new Source_random

    Raises:
        TypeError: if dtype is not a valid dtype
    """
    if not isinstance(dtype, streampu._ext.dtype):
        msg = f"type '{type(dtype)}' does not name an StreamPU datatype."
        raise TypeError(msg)
    class_name = f"Source_random_{str(dtype)}"
    class_type = getattr(streampu._ext.src, class_name)
    return class_type(max_data_size, seed)


def source_user_binary(
    max_data_size: int,
    filename: str,
    auto_reset: bool = True,
    fifo_mode: bool = False,
    dtype: streampu._ext.dtype = int16,
):
    """Build a new Source_user_binary.

    Args:
        max_data_size (int): output data size
        filename (str): File name
        auto_reset (bool): the source automatically restarts when it reaches the end of the file
        fifo_mode (bool): indicates if the file should be read in FIFO mode
        dtype (streampu._ext.dtype): Data type

    Returns:
        out (Module): a new Source_user_binary

    Raises:
        TypeError: if dtype is not a valid dtype
    """
    if not isinstance(dtype, streampu._ext.dtype):
        msg = f"type '{type(dtype)}' does not name an StreamPU datatype."
        raise TypeError(msg)
    class_name = f"Source_user_binary_{str(dtype)}"
    class_type = getattr(streampu._ext.src, class_name)
    return class_type(max_data_size, filename, auto_reset, fifo_mode)


def source_user(
    max_data_size: int,
    filename: str,
    auto_reset: bool = True,
    start_idx: int = 0,
    dtype: streampu._ext.dtype = int16,
):
    """Build a new Source_user.

    Args:
        max_data_size (int): output data size
        filename (str): File name
        auto_reset (bool): the source automatically restarts when it reaches the end of the file
        start_idx (int): reading offset
        dtype (streampu._ext.dtype): Data type

    Returns:
        out (Module): a new Source_user_binary

    Raises:
        TypeError: if dtype is not a valid dtype
    """
    if not isinstance(dtype, streampu._ext.dtype):
        msg = f"type '{type(dtype)}' does not name an StreamPU datatype."
        raise TypeError(msg)
    class_name = f"Source_user_{str(dtype)}"
    class_type = getattr(streampu._ext.src, class_name)
    return class_type(max_data_size, filename, auto_reset, start_idx)


__all__ = ["source_random", "source_user_binary", "source_user"]
