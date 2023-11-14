"""Add some magic functions to the class Task."""
from __future__ import annotations

from typing import Union

from aff3ct._ext.core import Socket, Task
from aff3ct._typing import SocketLike


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
    except Exception as exc:
        msg = f"'{self.__class__.__name__}' "
        msg += f"object has no attribute '{sck_name}'"
        raise AttributeError(msg) from exc


def _dir_impl(self: Task) -> dict:
    new_dir = object.__dir__(self)
    for sckt in self.sockets:
        new_dir.append(sckt.name)
    return new_dir


def _call_impl(self: Task,
               *args: tuple[SocketLike],
               **kwargs: dict[str, SocketLike]
               ) -> Union[Socket, tuple[Socket], None]:

    out_dir = Socket.directions.OUT

    inputs = [sckt for sckt in self.sockets if sckt.direction != out_dir]

    outputs = [sckt for sckt in self.sockets if sckt.direction == out_dir]
    outputs = [sckt for sckt in outputs if sckt.name != 'status']

    str_args = 'Args:\n'
    str_returns = 'Returns:\n'
    tsk_doc = f'{self.name} = {self.name}('
    for sckt in inputs:
        tsk_doc += f'{sckt.name}, '
    if inputs:
        tsk_doc = tsk_doc[0:-2]
    tsk_doc += f')\n{self.doc}\n'

    for sckt in inputs:
        len_ = sckt.n_elmts // self.module.n_frames
        str_args += f'\t{sckt.name} (Socket[{len_}'
        str_args += f', aff3ct.{str(sckt.dtype)}]): {sckt.doc}\n'

    for sckt in outputs:
        len_ = sckt.n_elmts // self.module.n_frames
        str_returns += f'\t{sckt.name} (Socket[{len_}'
        str_returns += f', aff3ct.{str(sckt.dtype)}]): {sckt.doc}\n'

    _call_impl.__doc__ = f'{tsk_doc}\n{str_args}\n{str_returns}\n'

    for i, arg in enumerate(args):
        inputs[i].reset()
        inputs[i].bind(arg)

    for key, sckt in kwargs.items():
        self[key].reset()
        self[key].bind(sckt)

    self.exec()

    for s_out in outputs:
        s_out.__class__ = Socket
        s_out.__mdl__ = self.module

    # Return a tuple of Sockets except that does not contain the status socket
    # If only one output socket, return this socket
    out = tuple(sckt for sckt in outputs if sckt.name != 'status')
    if len(out) > 1:
        return out

    if len(out) == 1:
        return out[0]

    return None


Task.__call__ = _call_impl
Task.__getattr__ = _getattr_impl
Task.__dir__ = _dir_impl

__all__ = ['Task']
