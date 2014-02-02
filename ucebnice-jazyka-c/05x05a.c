#include <stdio.h>

int main()
{
	int c;
	
	if ((c = getchar()) >= 'A' && c <= 'Z')
	{
		printf("%d \n", c);
	}
	
	return 0;
}
