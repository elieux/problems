import random
from sys import stdout

ops = ['R', 'B']

n = 100
stdout.write("%d\n" % n)
for i in range(n):
    k = random.randrange(1, 50)
    stdout.write("%d\n" % k)
    for j in range(k):
        stdout.write("%c" % ops[random.randrange(0, 2)])
    stdout.write("\n")