import random
import sys

figs = "prnqbPRNQB"

for x in range(1000):
	verts = ['.' for x in range(64)]
	nf = random.randrange(0,20);
	for i in range(nf):
		place = random.randrange(0, 64)
		fig = random.randrange(0, 9)
		verts[place] = figs[fig]
	
	place = random.randrange(0, 64)
	verts[place] = 'K'
	place = random.randrange(0, 64)
	verts[place] = 'k'

	for i in range(8):
		for j in range(8):
			sys.stdout.write(verts[i*8+j])
		sys.stdout.write('\n')
	sys.stdout.write('\n')
	
verts = ['.' for x in range(64)]
for i in range(8):
	for j in range(8):
		sys.stdout.write(verts[i*8+j])
	sys.stdout.write('\n')