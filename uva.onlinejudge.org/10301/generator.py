# 10301

import random
import sys

if len(sys.argv) != 2:
	print 'Usage: {0} <n-of-cases>'.format(sys.argv[0])
	exit(1)

n = int(sys.argv[1])
for i in range(n):
	print n
	k = random.randint(0, 100)
	for j in range(k):
		print random.random() * 20, random.random() * 20, random.random() * 20
print '-1'
