#include <stdio.h>

#undef DEBUG

#define grow(max, min) (((max) > (min)) ? ((max) - (min)) : 0)
#define interest(max, min, money) ((money) / (min) * grow(max, min))

int main()
{
#ifdef DEBUG
	printf("\tGrow between max=10, min=5 is %d\n", grow(10, 5));
	printf("\tGrow between max=5, min=5 is %d\n", grow(5, 5));
	printf("\tGrow between max=1, min=5 is %d\n", grow(1, 5));
#endif
	int maxinterest, min;
	int i;
	int d, m, p;
	
	scanf("%d", &d);
	while (d != 0)
	{
		scanf("%d", &m);
		min = 40000;
		maxinterest = 0;
		
		for (i = 1; i <= d; i++)
		{
			scanf("%d", &p);
			if (p < min)
				min = p;
			if (interest(p, min, m) > maxinterest)
#ifdef DEBUG
			{
				printf("\tMaxinterest=%d; new interest=%d, max=%d, min=%d, m=%d\n", maxinterest, interest(p, min, m), p, min, m);
#endif
				maxinterest = interest(p, min, m);
#ifdef DEBUG
			}
#endif
		}
		printf("%d\n", maxinterest);
		scanf("%d", &d);
	}
	
	return 0;
}
