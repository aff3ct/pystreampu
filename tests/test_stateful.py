# -*- coding: utf-8 -*-
"""Functionnal tests for Stateful."""

import streampu as spu
from streampu import Stateful
from streampu import uint32

n_elts=5

def processing( _,t, __): 
        inp = t.sock_in.numpy
        out = t.sock_out.numpy
        out[:] = inp[:] + 1
        return 0

class Example_increase(Stateful):
    N = spu.array([0])

    def __init__(self,N,dtype):
        self.N=N
        super().__init__()
        self.create_task("incr")
        self.create_socket_in(self["incr"],"sock_in",n_elts,dtype)
        self.create_socket_out(self["incr"],"sock_out",n_elts,dtype)
        self.create_codelet(self["incr"],processing)
    
    def execut(self):
         self.N=self["incr"](self.N)
         #print(self.N)
         return self.N


def test_stateful(dtype):

    src = spu.source_random(n_elts,dtype=dtype)
    spu.help(src)

    print(src['generate::out_data'])
    src['generate'].exec()

    #print(dir(spu))
    adding = Example_increase(src['generate::out_data'],dtype=dtype)
    
    for i in range(0,4):
        src['generate::out_data']=adding.execut()
        #src['generate::out_data']=adding["incr"](src['generate::out_data'])    #fonctionne aussi
    print("Output of source:", src['generate::out_data']) 

if __name__ == '__main__':
    test_stateful(uint32)

