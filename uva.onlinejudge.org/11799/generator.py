import random
from sys import stdout

stdout.write("50\n")
for j in range(50):
    N = random.randrange(1, 101)
    stdout.write("%d" % N)
    for i in range(N):
        stdout.write(" %d" % random.randrange(1, 10001))
    stdout.write("\n")