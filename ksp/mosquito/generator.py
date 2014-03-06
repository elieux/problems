import random
from sys import stdout

# M, P, L, E, R, S, N
for j in range(50):
    stdout.write("%d " % random.randrange(0, 100001)) # M
    stdout.write("%d " % random.randrange(0, 100001)) # P
    stdout.write("%d " % random.randrange(0, 100001)) # L
    stdout.write("%d " % random.randrange(0, 101)) # E
    stdout.write("%d " % random.randrange(1, 11)) # R
    stdout.write("%d " % random.randrange(1, 11)) # S
    stdout.write("%d " % random.randrange(1, 1001)) # N
    stdout.write("\n")