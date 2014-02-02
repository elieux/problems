#include <stdio.h>

int main()
{
	int i;
	int j;
	
	i = 5;
	j = 2;
	printf("i bylo %d\nj je %d\n", i, j);
	if (i == 5 && ++j == 3)
	{
		printf("podminka platna\n");
	}
	printf("i je %d\nj je %d\n\n", i, j);
	i = 4;
	j= 2;
	printf("i bylo %d\nj je %d\n", i, j);
	if (i == 5 && ++j == 3)
	{
		printf("podminka platna\n");
	}
	printf("i je %d\nj je %d\n\n", i, j);
	
	return 0;
}
