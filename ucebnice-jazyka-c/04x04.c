#include <stdio.h>

int main()
{
	int input;
	
	printf("Zadejte cenu bez dane :  ");
	scanf("%d", &input);
	printf("Prodejni cena s daní (25%%) :  %.0f\n", input * 1.25);
	
	return 0;
}
