#include <stdio.h>

int main()
{
	int i, n;
	float t1, t2;
	
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
	{
		scanf("%f %f", &t1, &t2);
		printf("%.0f\n", t1 * t2);
	}
	
	return 0;
}
