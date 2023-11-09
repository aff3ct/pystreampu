# encoding: utf-8
r"Add some magic functions to :aff3ct._ext.core.Task:"
from __future__ import annotations

from typing import Union

from aff3ct._ext.core import Task, Socket

def _getattr_impl(self: Task, sck_name: str) -> Union[tuple, Socket, None]:
    """Overload __getattr__ of aff3ct._ext.core.Task.

    task[socket_name] will return the socket named `socket_name`
    of the task.

    Args:
        self (Task): A Task
        sck_name (str): socket name

    Returns:
        out (Socket): the task socket named 'sck_name'

    Raises:
        AttributeError: if no socket is found
    """
    try:
        return self.module[f'{self.name}::{sck_name}']
    except:
        raise AttributeError(f"'{self.__class__.__name__}' object has no attribute '{sck_name}'")


def _dir_impl(self: Task) -> dict:
    from builtins import object
    new_dir = object.__dir__(self)
    for t in self.sockets:
        new_dir.append(t.name)
    return new_dir


def _call_impl(slf: Task, *args, **kwargs):
    inputs  = []
    outputs  = []
    str_args = "Args:\n"
    str_returns = "Returns:\n"
    for s in slf.sockets:
        if s.direction == Socket.directions.IN:
            str_args += f'\t{s.name} (Socket[{s.n_elmts/slf.module.n_frames}'
            str_args += f', {slf.module.n_frames}]):{s.doc}\n'

            inputs.append(s)
        elif s.direction == Socket.directions.OUT:
            str_returns += f'\t{s.name} (Socket[{s.n_elmts/slf.module.n_frames}'
            str_returns += f', {slf.module.n_frames}]):{s.doc}\n'

            outputs.append(s)
        else:
            str_args += f'\t{s.name} (Socket[{s.n_elmts/slf.module.n_frames}'
            str_args += f', {slf.module.n_frames}]):{s.doc}\n'
            inputs.append(s)
            #outputs.append(s)

    _call_impl.__doc__ = str_args + "\n" + str_returns + "\n"

    for i in range(len(args)):
        inputs[i].reset()
        inputs[i].bind(args[i])

    for k,s in kwargs.items():
        slf[k].__class__ = Socket
        slf[k].reset()
        slf[k].bind(s)

    slf.exec()

    for s_out in outputs:
        s_out.__class__ = Socket
        s_out.__mdl__ = slf.module

    rv = tuple([s for s in outputs if s.name != "status"])
    if len(rv) > 1:
        return rv
    elif len(rv) == 1:
        return rv[0]
    else:
        return None

Task.__call__ = _call_impl
Task.__getattr__ = _getattr_impl
Task.__dir__ = _dir_impl

__all__ = ["Task"]