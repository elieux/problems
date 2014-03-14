#include <stdio.h>
#include <stdlib.h>
#define false 0
#define true 1

int main()
{
	int c;
	int n, i, t, sc, lc;
	short int *p, *s, *l;
	
	lc = 0;
	sc = 0;
	
	scanf("%d", &n);
	s = malloc(n * sizeof(short int));
	l = malloc(n * sizeof(short int));
	p = malloc(n * sizeof(short int));
	for (i = 0; i < n; i++)
	{
		scanf("%d", &t);
		if (p[i] = (t % 2))
			l[lc++] = t;
		else
			s[sc++] = t;
	}
	
	do
	{
		c = false;
		for (i = 0; i < (lc - 1); i++)
		{
			if (l[i] < l[i + 1])
			{
				t = l[i];
				l[i] = l[i + 1];
				l[i + 1] = t;
				c = true;
			}
		}
	}
	while(c);
	
	do
	{
		c = false;
		for (i = 0; i < (sc - 1); i++)
		{
			if (s[i] > s[i + 1])
			{
				t = s[i];
				s[i] = s[i + 1];
				s[i + 1] = t;
				c = true;
			}
		}
	}
	while(c);
	
	lc = 0;
	sc = 0;
	printf("%d", (p[0] ? l[lc++] : s[sc++]));
	for (i = 1; i < n; i++)
		printf(" %d", (p[i] ? l[lc++] : s[sc++]));
	printf("\n");
	
	free(s);
	free(l);
	free(p);
	
	return 0;
}
