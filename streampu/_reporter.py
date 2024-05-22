import streampu._ext
from streampu._ext.reporter import Reporter_probe, Reporter
from streampu._ext import fmtflags, int16


def create_probe_value(
    self: Reporter_probe,
    name: str,
    unit: str = "",
    buffer_size: int = 100,
    socket_size: int = 1,
    fmt_flag: fmtflags = fmtflags.scientific,
    dtype: streampu._ext.dtype = int16,
):
    method_proxy = getattr(self, "_create_probe_value_" + str(dtype))
    return method_proxy(name, unit, buffer_size, socket_size, fmt_flag)


Reporter_probe.create_probe_value = create_probe_value


__all__ = ["Reporter_probe", "Reporter"]
