#include <stdio.h>
#include <ctype.h>

int main()
{
	int a;
	
	a = getchar();
	
	if (isalnum(a))
	{
		printf("Alfanumericky znak\n");
	}
	else
	{
		printf("Interpunkcni znak\n");
	}
	
	return 0;
}
