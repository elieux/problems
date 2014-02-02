#include <stdio.h>

int main()
{
	int a = 2;
	int b = 2;
	int c = 1;
	int e = 4;
	
	printf("%d\n", e / --a * b++ / c++);
	
	return 0;
}
