import sys
import random

if len(sys.argv) != 3:
	print("usage: {0} <number_of_cases> <max_number_of_people>".format(sys.argv[0]))
	exit(1)

n_cases = int(sys.argv[1])
max_n_people = int(sys.argv[2])

print(n_cases)
for case in range(n_cases):
	n_people = random.randrange(1, max_n_people)
	root = random.randrange(n_people)
	density = random.randrange(990, 999) / 1000
	print(n_people, root)
	for i in range(n_people):
		for j in range(i + 1, n_people):
			if random.random() > density:
				print(i, j)
	print(0, 0)
