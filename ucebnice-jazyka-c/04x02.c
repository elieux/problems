#include <stdio.h>

int main()
{
	int input;
	
	input = getchar();
	printf("%c (ASCII %d)\n", input + 1, input + 1);
	
	return 0;
}
