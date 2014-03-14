#include <stdio.h>
#include <time.h>

int main()
{
	int n, i, t;
	int p[30];
	
	for (i = 0; i < 30; i++)
	{
		p[i] = 0;
	}
	p[0] = 1;
	
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
	{
		for (t = i - 1; t > 0; t--)
		{
			p[t] = p[t - 1] + p[t];
		}
		printf("1");	/* aby nebyla mezera na zacatku radku */
		for (t = 1; t < i; t++)
		{
			printf(" %d", p[t]);
		}
		printf("\n");
	}
	
	return 0;
}
