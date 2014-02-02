#include <stdio.h>

int main()
{
	float a;
	float b;
	int c;
	
	printf("od: ");
	scanf("%f", &a);
	printf("do: ");
	scanf("%f", &b);
	for (c = (int) a; c <= b; c += 1)
	{
		if ((c > a) && ((c % 2) == 0))
		{
			printf("%d, ", c);
		}
	}
	
	return 0;
}
