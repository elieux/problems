#include <stdio.h>
#include <string.h>

#undef DEBUG

int main()
{
	const char bug[] = "BUG";
	const int bug_len = strlen(bug);
	
	int cases;
	int i, j, k;
	char one[128];
	int state;
	
	gets(one);
	sscanf(one, "%d", &cases);
	
	for (i = 1; i <= cases; i++)
	{
		gets(one);
#ifdef DEBUG
		printf("\tscanned: %s\n", one);
		fflush(stdout);
#endif
		while (one[0] != '\0')
		{
			state = 0;
			j = 0;
			while (one[j] != '\0')
			{
#ifdef DEBUG
				printf("\tcase %3d; char %3d; state %3d\n", i, j, state);
				fflush(stdout);
#endif
				if (one[j] == bug[state])
					state++;
				else
				{
					for (k = 0; k < state; k++)
						putchar(bug[k]);
					state = 0;
					putchar(one[j]);
				}
				if (state == bug_len)
					state = 0;
				j++;
			}
#ifdef DEBUG
				fflush(stdout);
#endif
			printf("\n");
			gets(one);
#ifdef DEBUG
			printf("\tscanned: %s\n", one);
			fflush(stdout);
#endif
		}
		printf("\n");
	}
	
	return 0;
}
