import sys
import random

if len(sys.argv) != 3:
	print("usage: {0} <number_of_cases> <max_number_abs_value>".format(sys.argv[0]))
	exit(1)

n_cases = int(sys.argv[1])
max_number_abs_value = int(sys.argv[2])

print(n_cases)
for i in range(n_cases):
	pair = [ random.randrange(-max_number_abs_value + 1, max_number_abs_value) for i in range(2) ]
	print(*pair)
