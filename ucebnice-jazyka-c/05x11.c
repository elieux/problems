#include <stdio.h>
#include <ctype.h>

int main()
{
	int a = 0;
	int b = 0;
	int c;
	
	while ((c = getchar()) != '\n')
	{
		if (isupper(c))
		{
			a += 1;
		}
		if (islower(c))
		{
			b += 1;
		}
	}
	printf("velkych pismen: %d\nmalych pismen: %d\n", a, b);
	
	return 0;
}
