#include <stdio.h>

int main()
{
	int a = 2;
	int c = 1;
	int e = 4;
	
	printf("%d\n", a++ / ++c * --e);
	
	return 0;
}
