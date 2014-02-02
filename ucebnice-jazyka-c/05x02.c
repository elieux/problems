#include <stdio.h>

int main()
{
	int a;
	int b;
	int c;
	
	scanf("%d %d", &a, &b);
	c = b;
	printf("Mensi cislo :  %d\n", (b < a) ? (c = a, b) : a);
	printf("Vetsi cislo :  %d\n", c);
	
	return 0;
}
