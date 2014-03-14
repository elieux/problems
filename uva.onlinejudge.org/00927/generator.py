# 00927

import sys
import random

if len(sys.argv) != 2:
	print("usage: {0} <number_of_cases>".format(sys.argv[0]))
	exit(1)

n_cases = int(sys.argv[1])

print n_cases
for i in range(n_cases):
	polydegree = random.randint(1, 20)
	polycoeffs = [str(random.randint(0, 100)) for x in range(polydegree + 1)]
	print polydegree, ' '.join(polycoeffs)
	d = random.randint(1, 100000)
	print d
	k = random.randint(1, 1000000)
	print k
