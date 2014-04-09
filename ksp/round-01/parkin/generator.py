import random
from sys import stdout

stdout.write("100\n")
for j in range(100):
    N = random.randrange(1, 21)
    stdout.write("%d\n" % N)
    stdout.write("%d" % random.randrange(0, 100))
    for i in range(N-1):
        stdout.write(" %d" % random.randrange(0, 100))
    stdout.write("\n")