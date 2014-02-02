#include <stdio.h>

int main()
{
	int cases;
	int i, j, diffs;
	char one[128], two[128];
	
	scanf("%d", &cases);
	
	for (i = 1; i <= cases; i++)
	{
		scanf("%s", one);
		scanf("%s", two);
		
		j = 0;
		diffs = 0;
		while (one[j] != '\0')
		{
			if (one[j] != two[j])
				diffs++;
			j++;
		}
		printf("The numbers differ in %d positions.\n", diffs);
	}
	
	return 0;
}

