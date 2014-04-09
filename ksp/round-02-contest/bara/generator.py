from sys import stdout
import random

cases = 300
stdout.write("%d\n" % cases)
for i in range(cases):
    juice = random.randrange(2,10000)
    count = random.randrange(1,juice)
    stdout.write("%d %d\n" %(juice, count))
    stdout.write("%d" % random.randrange(0, 50000))
    for j in range(1, juice):
        stdout.write(" %d" % random.randrange(0,50000))
    stdout.write("\n")
