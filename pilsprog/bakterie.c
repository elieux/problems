#include <stdio.h>

int main()
{
	int n, mlade, stare, vzniklo, t, i;
	
	scanf("%d %d", &mlade, &t);
	
	t = 2 * t; /* pocet pulhodin */
	stare = 0;
	
	for (i = 1; i <= t; i++)
	{
		vzniklo = mlade + stare;
		n = vzniklo + mlade;
		stare = mlade;
		mlade = vzniklo;
	}
	printf("%d\n", n);
	
	return 0;
}
