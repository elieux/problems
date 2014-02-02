#include <stdio.h>

int main()
{
	int i, n, soucet, rozdil, t;
	
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
	{
		scanf("%d %d", &soucet, &rozdil);
		if (soucet < rozdil)
		{
			t = soucet;
			soucet = rozdil;
			rozdil = t;
		}
		if (((soucet - rozdil) % 2))
			printf("chyba!\n");
		else
			printf("%d %d\n", (soucet - rozdil) / 2, (soucet + rozdil) /2);
	}
	
	return 0;
}
