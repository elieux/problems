import string
import random
from sys import stdout

for j in range(100):
    N = random.randrange(1, 101)
    stdout.write("%d\n" % N)
    for n1 in range(N):
        if random.random() > 0.05:
            stdout.write("%d" % (n1+1))
            for n2 in range(N):
                if random.random() > 0.97:
                    stdout.write(" %d" % random.randrange(1, N+1))
            stdout.write(" 0\n")
    stdout.write("0\n")
    Q = random.randrange(1, N+1)
    stdout.write("%d" % Q)
    for n3 in range(Q):
        stdout.write(" %d" % random.randrange(1, N+1))
    stdout.write("\n")
stdout.write("0\n")
