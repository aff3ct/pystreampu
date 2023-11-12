from __future__ import annotations

from typing import Union

from aff3ct._ext.core import Sequence, Socket


def _unique(in_list: list):
    out_list = []
    for elt in in_list:
        if elt not in out_list:
            out_list.append(elt)
    return out_list


def _get_firsts(s: Socket):
    def visit(s: Socket, visited: list[Socket]):
        tsk = s.task
        visited.append(tsk)
        if len(tsk.inputs) == 0 and len(tsk.forwards) == 0 and not tsk.is_bound():
            return [tsk]
        else:
            out = []
            lbnd = _unique([si.bound_socket for si in tsk.inputs])
            lbnd += _unique([si.bound_socket for si in tsk.forwards])
            for b in lbnd:
                try:
                    if b.task not in visited:
                        lt = visit(b, visited)
                        for t in lt:
                            out.append(t)
                except Exception as exc:
                    print(exc)
                    out.append(b.task)
        return out
    return visit(s, [])


def from_socket(sockets = Union[Socket, list[Socket]], *args: tuple, **kwargs: dict):
    firsts = []
    if not isinstance(sockets, list):
        sockets = [sockets]
    for s_itm in sockets:
        while hasattr(s_itm, "_mrv"):
            s_itm = s_itm._mrv
        local_firsts = _get_firsts(s_itm)
        for first in local_firsts:
            if first not in firsts:
                firsts.append(first)

    return Sequence(firsts, [], [], *args, **kwargs)

Sequence.from_socket = from_socket
__all__ = ["Sequence"]
