#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 1024
#define MAX 42000000

#define EMPTY(x) ((x) == 0xFFFFFFFFu)
#define NEXT(x) (0 == ((x) % 2) ? (x) / 2 : (x) * 3 + 1)

unsigned int *next;

void tle() {
	while (1);
}

void error(char *msg, unsigned int no) {
	/*fprintf(stderr, msg);
	fprintf(stderr, ": %u\n", no);*/
	tle();
}

void doit(unsigned int a, unsigned int b) {
	unsigned int xa, xb, sa, sb, c;
	unsigned int *seqa, *seqb;
	bool stopa, stopb;
	
	seqa = (unsigned int *)malloc(sizeof(unsigned int) * MAX);
	seqb = (unsigned int *)malloc(sizeof(unsigned int) * MAX);
	
	memset((void *)seqa, 0xFF, sizeof(unsigned int) * MAX);
	memset((void *)seqb, 0xFF, sizeof(unsigned int) * MAX);
	
	xa = a;
	xb = b;
	sa = 0;
	sb = 0;
	stopa = false;
	stopb = false;
	while (true)
	{
		if (!stopa)
		{
			if (!EMPTY(seqa[xa]))
				stopa = true;
			else
				seqa[xa] = sa;
		}
			
		if (!stopb)
		{
			if (!EMPTY(seqb[xb]))
				stopb = true;
			else
				seqb[xb] = sb;
		}
		
		if (!EMPTY(seqa[xb]) || !EMPTY(seqb[xa]))
			break;
		
		if (!stopa)
		{
			sa++;
			xa = next[xa];
			if (xa >= MAX)
			{
				stopa = true;
				xa = MAX;
				error("xa >= MAX", xa);
			}
		}
		if (!stopb)
		{
			sb++;
			xb = next[xb];
			if (xb >= MAX)
			{
				stopb = true;
				xb = MAX;
				error("xb >= MAX", xb);
			}
		}
	}
	
	if (!stopb && !EMPTY(seqa[xb]))
	{
		sa = seqa[xb];
		c = xb;
	}
	else if (!stopa && !EMPTY(seqb[xa]))
	{
		sb = seqb[xa];
		c = xa;
	}
	else
		error("stopped a and b", 0);
	
	printf("%u needs %u steps, %u needs %u steps, they meet at %u\n", a, sa, b, sb, c);
}

int main(int argc, char *argv[]) {
	char line[LINE_LENGTH];
	unsigned int a, b, i;
	
	argc = argc;
	argv = argv;
	
	next = (unsigned int *)malloc(sizeof(unsigned int) * MAX);
	for (i = 0; i < MAX; i++)
		next[i] = NEXT(i);
	
	while (true)
	{
		fgets(line, LINE_LENGTH, stdin);
		sscanf(line, "%u %u", &a, &b);
		if (0 == a && 0 == b)
			break;
		
		doit(a, b);
	}
	
	return 0;
}
