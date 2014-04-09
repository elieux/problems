import string
import random
from sys import stdout

stdout.write("100\n")
for j in range(100):
    N = random.randrange(1, 26)
    stdout.write("\n")
    stdout.write("%s\n" % string.ascii_uppercase[N])
    for n1 in range(N + 1):
        for n2 in range(n1 + 1, N + 1):
            if random.random() > 0.3:
                stdout.write("%s%s\n" % (string.ascii_uppercase[n1], string.ascii_uppercase[n2]))