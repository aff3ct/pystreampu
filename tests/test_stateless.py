# -*- coding: utf-8 -*-
"""Functionnal tests for Stateless."""
import numpy as np

from streampu import array
from streampu import Stateless
from streampu import uint16
from streampu import help
from streampu import Sequence
def test_stateless(dtype):
    """Test Stateless module

    Args:
        dtype (streampu._ext.dtype): Data type
    """
    npx = np.array([[1, 2, 3, 4]], dtype=dtype.numpy)
    x = array(npx)
    mdl = Stateless()
    assert mdl is not None

    tsk = mdl.create_task("inc")
    assert tsk is not None

    mdl.create_socket_in(tsk,"sock_in",4,dtype)
    mdl.create_socket_out(tsk,"sock_out",4,dtype)
    help(mdl)

    def processing( _,t, __): #processing(m,t,id)
        inp = t.sock_in.numpy
        out = t.sock_out.numpy
        out[:] = inp[:] + 1
        return 0
    
    mdl.create_codelet(tsk, processing)    
    
    y =tsk(x)
    """
    Other way to write :

    y=mdl["inc"](x)

    or

    y = mdl.inc(x)
    """
    print(y)


    #mdl["inc::sock_in"].bind(x) # =x
    #mdl["inc"].exec()
    #print(mdl["inc::sock_out"])

    #seq = Sequence(x.task)
    #seq.export_dot("test.dot")

if __name__ == '__main__':
    test_stateless(uint16)

