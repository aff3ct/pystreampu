from aff3ct._ext.core import Sequence

def _get_firsts(s):
    def visit(s, visited):
        visited.append(s.task)
        if len(s.task.inputs)==0 and len(s.task.forwards)==0 and not s.task.is_bound():
            return [s.task]
        else:
            out = []
            lbnd = list(set([si.bound_socket for si in s.task.inputs])) + list(set([si.bound_socket for si in s.task.forwards]))
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
    f = []
    if type(s) is not list:
        s = [s]
    for s_itm in s:
        while hasattr(s_itm, "__mrv__"):
            s_itm = s_itm.__mrv__
        lf = _get_firsts(s_itm)
        for lf_it in lf:
            if lf_it not in f:
                f.append(lf_it)

    return Sequence(f,[],[], *args, **kwargs)

Sequence.from_socket = from_socket
__all__ = ["Sequence"]