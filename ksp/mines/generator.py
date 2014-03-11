import string
import random
from sys import stdout

def gen(num, min, max):
    for j in range(num):
        N = random.randrange(min, max)
        M = random.randrange(min, max)
        stdout.write("%d %d\n" % (N, M))
        
        start = 0, 0
        end = N - 1, M - 1
        
        mines = []
        for x in range(N):
            for y in range(M):
                if (x, y) != start and (x, y) != end:
                    if random.random() < 0.1:
                        mines.append("%d %d\n" % (x, y))
                    elif random.random() < 0.001:
                        start = x, y
                    elif random.random() < 0.001:
                        end = x, y
        stdout.write("%d\n" % len(mines))
        for mine in mines:
            stdout.write(mine)
        stdout.write("%d %d\n" % start)
        stdout.write("%d %d\n" % end)
    stdout.write("0 0\n")

# gen(1000, 1, 10)
# gen(100, 10, 100)
# gen(10, 100, 500)