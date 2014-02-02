#include <stdio.h>
#include <ctype.h>

int main()
{
	int a;
	
	a = getchar();
	
	if (isalnum(a))
	{
		if (isdigit(a))
		{
			printf("cislice : '%c'\n", a);
		}
		if (islower(a))
		{
			printf("male pismeno : '%c'\n", a);
		}
		if (isupper(a))
		{
			printf("velke pismeno : '%c'\n", a);
		}
	}
	else
	{
		printf("interpunkcni znak : '%c'\n", a);
	}
	
	return 0;
}
