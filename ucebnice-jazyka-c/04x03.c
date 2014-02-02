#include <stdio.h>

int main()
{
	int input;
	
	scanf("%d", &input);
	if ((input < 256) && (input >= 0))
	{
		printf("%2Xh\n", input);
	}
	
	return 0;
}
