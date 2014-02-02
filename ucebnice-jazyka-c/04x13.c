#include <stdio.h>

int main()
{
	float a;
	float b;
	float c;
	
	scanf("%f %f %f", &a, &b, &c);
	printf("%.2f\n", (a + b + c) / 3);
	
	return 0;
}
