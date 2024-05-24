"""Add some magic functions to the class Task."""

from __future__ import annotations

from typing import Union, Any

from streampu._ext.core import Socket, Task
from streampu._typing import SocketLike
import numpy as np
from streampu._ext import exceptions as exc

Task.call_auto_exec = True


def _setattr_impl(self: Task, attr: str, value: Any) -> Union[tuple, Socket, None]:
    """Overload __setattr__ of streampu._ext.core.Task.

    Args:
        self (Task): A Task
        attr (str): attribute name
        value (any): Value to set
    """
    if attr in [s.name for s in self.sockets]:
        sck = self.module[f"{self.name}::{attr}"]
        sck.bind(value)
    else:
        return object.__setattr__(self, attr, value)


def _getattr_impl(self: Task, attr: str) -> Union[tuple, Socket, None]:
    """Overload __getattr__ of streampu._ext.core.Task.

    task[socket_name] will return the socket named `socket_name`
    of the task.

    Args:
        self (Task): A Task
        attr (str): socket name

    Returns:
        out (Socket): the task socket named 'sck_name'
    """
    if attr in [s.name for s in self.sockets]:
        return self.module[f"{self.name}::{attr}"]

    return object.__getattribute__(self, attr)


def _dir_impl(self: Task) -> dict:
    new_dir = object.__dir__(self)
    for sckt in self.sockets:
        new_dir.append(sckt.name)
    return new_dir


def _get_task_doc(self):
    out_dir = Socket.directions.OUT

    inputs = [sckt for sckt in self.sockets if sckt.direction != out_dir]

    outputs = [sckt for sckt in self.sockets if sckt.direction == out_dir]
    outputs = [sckt for sckt in outputs if sckt.name != "status"]

    str_args = "Args:\n"
    str_returns = "Returns:\n"
    tsk_doc = f"{self.name} = {self.name}("
    for sckt in inputs:
        tsk_doc += f"{sckt.name}, "
    if inputs:
        tsk_doc = tsk_doc[0:-2]
    tsk_doc += f")\n"

    for sckt in inputs:
        len_ = sckt.n_elmts // self.module.n_frames
        str_args += f"\t{sckt.name}: Socket[{len_}"
        str_args += f", streampu.{str(sckt.dtype)}]\n"

    for sckt in outputs:
        len_ = sckt.n_elmts // self.module.n_frames
        str_returns += f"\t{sckt.name}: Socket[{len_}"
        str_returns += f", streampu.{str(sckt.dtype)}]\n"

    return f"{tsk_doc}\n{str_args}\n{str_returns}\n"


Task._get_task_doc = _get_task_doc


def _call_impl(
    self: Task,
    *args: tuple[SocketLike],
    raw_data=False,
    no_doc=False,
    **kwargs: dict[str, SocketLike],
) -> Union[Socket, tuple[Socket], None]:

    out_dir = Socket.directions.OUT

    inputs = [sckt for sckt in self.sockets if sckt.direction != out_dir]
    outputs = [sckt for sckt in self.sockets if sckt.direction == out_dir]
    outputs = [sckt for sckt in outputs if sckt.name != "status"]

    if not no_doc:
        _call_impl.__doc__ = self._get_task_doc()

    for i, arg in enumerate(args):
        inputs[i].reset()
        inputs[i].bind(arg, raw_data=raw_data)

    for key, sckt in kwargs.items():
        self[key].reset()
        self[key].bind(sckt, raw_data=raw_data)

    if Task.call_auto_exec:
        try:
            self.exec()
        except exc.ProcessingAborted:
            pass

    if raw_data:
        out = tuple(np.array(sckt, copy=False) for sckt in outputs)
        if len(out) == 1:
            return out[0]

        return None

    for s_out in outputs:
        s_out._mdl = self.module

    # Return a tuple of Sockets except that does not contain the status socket
    # If only one output socket, return this socket
    out = tuple(sckt for sckt in outputs)
    if len(out) > 1:
        return out

    if len(out) == 1:
        return out[0]

    return None


Task.__call__ = _call_impl
Task.__getattr__ = _getattr_impl
Task.__setattr__ = _setattr_impl
Task.__dir__ = _dir_impl

__all__ = ["Task"]