#include <stdio.h>
#include <string.h>
#include <math.h>

#define floor(x) ((double) ((int) (x)))
#define ceil(x) ((double) (((int) (x)) + 1))
#define round(x) (((((int) ((x) * 10)) % 10) < 5) ? floor(x) : ceil(x))
#define roundn(x, n) (round((x) * pow(10, (n))) / pow(10, (n)))

#undef DEBUG

int main()
{
	const char err = '#';
	
	int cases;
	int i, j;
	char one[128];
	int errors, total;
	
	gets(one);
	sscanf(one, "%d", &cases);
	
	for (i = 1; i <= cases; i++)
	{
		gets(one);
#ifdef DEBUG
		printf("\tscanned: %s\n", one);
		fflush(stdout);
#endif
		total = 0;
		errors = 0;
		while (one[0] != '\0')
		{
			j = 0;
			while (one[j] != '\0')
			{
				if (one[j] == err)
					errors++;
				total++;
#ifdef DEBUG
				printf("\tcase %3d; char %3d; total %3d; errors %3d; effeciency %5f\n", i, j, total, errors, 100.0 * ((float) (total - errors)) / ((float) total));
				fflush(stdout);
#endif
				j++;
			}
			printf("\n");
			gets(one);
#ifdef DEBUG
			printf("\tscanned: %s\n", one);
			fflush(stdout);
#endif
		}
		printf("The efficiency ratio is %3f%%.\n", roundn(100.0 * ((float) (total - errors)) / ((float) total), 1));
	}
	
	return 0;
}
