#include <stdio.h>
#include <ctype.h>

int main()
{
	int a;
	int b;
	
	a = getchar();
	b = getchar();
	
	if (isxdigit(a) && isxdigit(b))
	{
		if (islower(a))
		{
			a -= 'a' - '0' - 10;
		}
		if (isupper(a))
		{
			a -= 'A' - '0' - 10;
		}
		a -= '0';
		if (islower(b))
		{
			b -= 'a' - '0' - 10;
		}
		if (isupper(b))
		{
			b -= 'A' - '0' - 10;
		}
		b -= '0';
		printf("h = %d\n", a * 16 + b);
	}
	
	return 0;
}
