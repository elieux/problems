#include <stdio.h>

int main()
{
	int a;
	long int b = 1;
	int c;
	
	printf("cislo: ");
	scanf("%d", &a);
	for (c = a; c != 0; c -= 1)
	{
		if ((b * c) <= 0)
		{
			b = -1;
			break;
		}
		b *= c;
	}
	printf("%d! = %ld\n", a, b);
	
	return 0;
}
