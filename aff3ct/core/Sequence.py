from ..builtins.core import Sequence

def get_firsts(s):
    def visit(s, visited):
        visited.append(s.task)
        if len(s.task.inputs)==0 and not s.task.is_bound():
            return [s.task]
        else:
            out = []
            lbnd = list(set([si.bound_socket for si in s.task.inputs]))
            for b in lbnd:
                try:
                    if b.task not in visited:
                        lt = visit(b,visited)
                        for t in lt : out.append(t)
                except:
                    out.append(b.task)
        return out
    return visit(s,[])

def from_socket(s, *args, **kwargs):
    f = get_firsts(s)
    return Sequence(f,[],[], *args, **kwargs)

Sequence.from_socket = from_socket
__all__ = ["Sequence"]