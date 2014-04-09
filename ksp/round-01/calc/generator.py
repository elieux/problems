import random
from sys import stdout

ops = ['+', '-', '*']

n = 1000
stdout.write("%d\n" % n)
for i in range(n):
    stdout.write("%d" % random.randrange(0, 1000))
    stdout.write(" %c " % ops[random.randrange(0, 3)])
    stdout.write("%d" % random.randrange(0, 1000))
    stdout.write("\n")