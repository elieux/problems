#include <stdio.h>
#include <ctype.h>

int main()
{
	int a = 0;
	int b;
	int c;
	int d;
	
	printf("Pocet cisel: ");
	scanf("%d", &b);
	for (c = 0; c < b; c += 1)
	{
		printf("Zadej %d. cislo : ", c + 1);
		scanf("%d", &d);
		if ((d >= 25) && (d <= 38))
		{
			a += 1;
		}
	}
	printf("Pocet cisel v <25; 38>: %d\n", a);
	
	return 0;
}
