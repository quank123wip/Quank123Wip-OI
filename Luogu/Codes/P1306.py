import numpy
from math import gcd
A=numpy.array([[1,1],[1,0]])
Fib=numpy.array([1,1])
n,m=input().split()
p=gcd(int(n),int(m))
if p<=2:
    print(1)
else:
    p-=2
    while p:
        if p&1:
            Fib=numpy.matmul(Fib,A)
        A=numpy.matmul(A,A)
        p>>=1
    print(Fib[0])
