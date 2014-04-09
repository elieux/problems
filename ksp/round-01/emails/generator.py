# 00924

import sys
import random

if len(sys.argv) != 3:
	print("usage: {0} <number_of_employees> <number_of_tests>".format(sys.argv[0]))
	exit(1)

n_employees = int(sys.argv[1])
n_tests = int(sys.argv[2])

assert(1 <= n_employees <= 2500)
assert(0 <= n_tests < 60)

print(n_employees)
for i in range(n_employees):
	friends = []
	for j in range(i + 1, n_employees):
		if len(friends) + 1 < 15 and random.random() > 0.95:
			friends.append(j)
	print(str(len(friends)) + "".join(" " + str(x) for x in friends))

print(n_tests)
for i in range(n_tests):
	print(str(random.randrange(0, n_employees)))
