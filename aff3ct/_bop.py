# encoding: utf-8
"""Provides a binary operator (bop) factory."""

import aff3ct._ext
from aff3ct._ext import dtype, int8
from aff3ct._ext.core import Module


def bop(
    n_in0: int,
    n_in1: int,
    bop_name: str,
    input_type: dtype = int8,
    output_type: dtype = int8,
) -> Module:
    """Build a binary operator module.

    Args:
        n_in0 (int): Number of elements of input socket in0
        n_in1 (int): Number of elements of input socket in1
        bop_name (str): Name of the binary operator to instantiate
        input_type (dtype): Input data type
        output_type (dtype): Output data type

    Returns:
        out (Module): AFF3CT module binary operator

    Raises:
        TypeError: if input_type or output_type are not dtypes
        AttributeError: if no binary operator can be built
    """
    if not issubclass(type(input_type), dtype):
        ex_msg = f"type '{type(input_type)}' does not name an AFF3CT dtype."
        raise TypeError(ex_msg)

    if not issubclass(type(output_type), dtype):
        ex_msg = f"type '{type(output_type)}' does not name an AFF3CT dtype."
        raise TypeError(ex_msg)

    try:
        attr_name = f'Binaryop_{bop_name}_{input_type.name}_{output_type.name}'
        return getattr(aff3ct._ext.bop, attr_name)(n_in0, n_in1)
    except AttributeError as exc:
        ex_msg = f"binary operator '{attr_name}' does not exist."
        raise AttributeError(ex_msg) from exc
