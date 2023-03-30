'''import numpy as np
import pyaf

class class_with_loopy_method():
    def __init__(self, N):
        self.N = N

    @pyaf.jit(stats=True)
    def execute(self, s):
        for i in pyaf.range(self.N, dtype=np.float32):
            s += i
        return s


t = class_with_loopy_method(10)

N = 12

@pyaf.jit(stats=True)
def foo(s):
    for i in pyaf.range(N, dtype=np.float32):
        s += i
    return s

o = pyaf.array(12.3, 1, dtype = np.float32)

s  = foo (o)

print(s)



add1  = pyaf.builtins.bop.Binaryop_add_float32_float32(10)
add2  = pyaf.builtins.bop.Binaryop_add_float32_float32(10)
add3  = pyaf.builtins.bop.Binaryop_add_float32_float32(10)

add3["perform::in1"].bind(add1["perform::out"])
add3["perform::in2"].bind(add2["perform::out"])

seq = pyaf.builtins.core.Sequence([add1.perform, add2.perform], [add3.perform],[],1)
seq.export_dot('test.dot')

sse = pyaf.builtins.sse.Subsequence(seq)
'''
