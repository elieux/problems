#include <stdio.h>

int main()
{
	int a = 2;
	int b = 2;
	int d = 0;
	int e = 4;
	
	printf("%d\n", a %= b = d = 1 + e / 2);
	
	return 0;
}
