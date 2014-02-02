#include <stdio.h>

int main()
{
	int t, p, q;
	
	scanf("%d %d", &p, &q);
	
	t = ((p % q) ? (p / q) : (p / q - 1));
	if (p > 2 * q)
		printf("%d %d\n", t * q, (t - 1) * q);
	else
		printf("Reseni neexistuje.\n");
	
	return 0;
}
