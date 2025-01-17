# -*- coding: utf-8 -*-
r"""Defines some factory for the wrapping of Probes."""

import streampu._ext
from streampu._ext import int8
from streampu._ext.prb import (
    AProbe,
    Probe_latency,
    Probe_occurrence,
    Probe_throughput,
    Probe_time,
    Probe_timestamp,
)
from streampu._ext.reporter import Reporter_probe


def probe_value(
    size: int,
    col_name: str,
    reporter: Reporter_probe,
    dtype: streampu._ext.dtype = int8,
) -> AProbe:
    """Build a new Probe_Value module.

    Args:
        size (int): size of the socket to probe
        col_name (str): Name of the column for display
        reporter (Reporter_probe): Reporter to attach the probe
        dtype (streampu._ext.dtype): Input data type

    Returns:
        AProbe: a new Probe_Value

    Raises:
        TypeError: if dtype input is not a valid dtype
    """
    if not isinstance(dtype, streampu._ext.dtype):
        msg = f"type '{type(dtype)}' does not name an StreamPU datatype."
        raise TypeError(msg)
    name = f"Probe_value_{str(dtype.name)}"
    prb_class = getattr(streampu._ext.prb, name)
    return prb_class(size, col_name, reporter)


__all__ = [
    "AProbe",
    "Probe_latency",
    "Probe_occurrence",
    "Probe_throughput",
    "Probe_time",
    "Probe_timestamp",
    "probe_value",
]
