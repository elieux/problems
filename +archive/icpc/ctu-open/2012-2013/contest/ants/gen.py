
#L=[1-15] A=[1-L+1]
#A x P=[1-L+1]

import random

dirs = ['L', 'R']

for case in range(30):
	length = random.randint(1,15)
	ants = random.randint(1, length + 1)
	print length, ants
	
	vec = []
	while len(vec) < ants:
		newpos = random.randint(0, length)
		if (0 == vec.count(newpos)):
			vec.append(newpos)
	
	vec.sort()
	for pos in vec:
		print pos, random.choice(dirs)
