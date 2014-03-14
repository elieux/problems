# 10927

import random
import sys

if (len(sys.argv) != 3):
	print 'Usage: {0} <n-of-cases> <n-of-poles>'.format(sys.argv[0])
	exit(1)

cases = int(sys.argv[1])
poles = int(sys.argv[2])

for case in range(cases):
	print str(poles)
	for pole in range(poles):
		while True:
			x, y, z = random.randint(-100, 100), random.randint(0, 100), random.randint(0, 100)
			if x != 0 or y != 0:
				break
		print x, y, z
print str(0)
