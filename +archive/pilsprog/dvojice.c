#include <stdio.h>
#include <stdlib.h>
#define false 0
#define true 1
#define max 80000

int main()
{
	short int a[max];
	int i, j, p, s;
	char t[200];
	int b[1000];
	
	for (i = 0; i < max; i++)
		a[i] = true;
	a[1] = false;
	for (i = 2; i < (max / 2); i++)
		if (a[i] == true)
			for (j = 2; (j * i) < max; j++)
				a[j * i] = false;
	
	s = 0;
	i = 3;
	do
	{
		gets(t);
		if (t[0] != 0)
		{
			p = atoi(t);
			for (; s < p; i++)
				if ((a[i] == true) && (a[i - 2] == true))
					b[++s] = i - 2;
			printf("(%d, %d)\n", b[p], b[p] + 2);
		}
	}
	while (t[0] != 0);
	
	return 0;
}
