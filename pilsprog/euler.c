#include <stdio.h>
#include <math.h>
#define MAX 1862
#define true 1
#define false 0

int round(double a)
{
	if (a - ((double) floor(a)) < 0.5)
		return floor(a);
	else
		return ceil(a);
}

int is_prime(int a)
{
	int i;
	
	if (a == 1)
		return false;
	if (!(a % 2))
		return false;
	if (!(a % 3))
		return false;
	for (i = 5; i <= sqrt(a); i += 6)
		if (!(a % i))
			return false;
	for (i = 7; i <= sqrt(a); i += 6)
		if (!(a % i))
			return false;
	return true;
}

int main()
{
	int a, b;
	int i, j;
	
	scanf("%d %d", &a, &b);
	
	j = 0;
	for (i = a; i <= b; i++)
		if (is_prime(i * i + i + 41))
			j++;
	
	printf("%d\n", round(100 * (((double) j) / ((double) (b - a + 1)))));
	
	return 0;
}
