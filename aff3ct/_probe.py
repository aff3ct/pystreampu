r"""Defines some factory for the wrapping of Probes."""

import aff3ct._ext
from aff3ct._ext import int8
from aff3ct._ext.reporter import Reporter_probe

from aff3ct._ext.prb import (AProbe, Probe_latency, Probe_occurrence,
                             Probe_throughput, Probe_time, Probe_timestamp)


def probe(size: int,
          col_name: str,
          reporter: Reporter_probe,
          n_frames: int = 1,
          dtype: aff3ct._ext.dtype = int8) -> AProbe:
    """Build a new Probe module.

    Args:
        size (int): size of the socket to probe
        col_name (str): Name of the column for display
        reporter (Reporter_probe): Reporter to attach the probe
        n_frames (int): Number of frames to process at each execution
        dtype (aff3ct._ext.dtype): Input data type

    Returns:
        AProbe: a new Probe

    Raises:
        TypeError: if dtype input is not a valid dtype
    """
    if not isinstance(dtype, aff3ct._ext.dtype):
        msg = f"type '{type(dtype)}' does not name an AFF3CT datatype."
        raise TypeError(msg)
    name = f'Probe_{str(dtype.name)}'
    prb_class = getattr(aff3ct._ext.prb, name)
    return prb_class(size, col_name, reporter, n_frames)


def probe_value(size: int,
                col_name: str,
                reporter: Reporter_probe,
                n_frames: int = 1,
                dtype: aff3ct._ext.dtype = int8) -> AProbe:
    """Build a new Probe_Value module.

    Args:
        size (int): size of the socket to probe
        col_name (str): Name of the column for display
        reporter (Reporter_probe): Reporter to attach the probe
        n_frames (int): Number of frames to process at each execution
        dtype (aff3ct._ext.dtype): Input data type

    Returns:
        AProbe: a new Probe

    Raises:
        TypeError: if dtype input is not a valid dtype
    """
    if not isinstance(dtype, aff3ct._ext.dtype):
        msg = f"type '{type(dtype)}' does not name an AFF3CT datatype."
        raise TypeError(msg)
    name = f'Probe_value_{str(dtype.name)}'
    prb_class = getattr(aff3ct._ext.prb, name)
    return prb_class(size, col_name, reporter, n_frames)


__all__ = ['AProbe', 'Probe_latency', 'Probe_occurrence', 'Probe_throughput',
           'Probe_time', 'Probe_timestamp', 'probe', 'probe_value']
