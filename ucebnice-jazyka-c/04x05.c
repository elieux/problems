#include <stdio.h>

int main()
{
	int width;
	int height;
	
	printf("Zadejte delku a sirku :  ");
	scanf("%d %d", &height, &width);
	printf("Obdelnik o delce %d a sirce %d ma obsah %d\n", height, width, height * width);
	
	return 0;
}
