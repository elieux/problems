#include <stdio.h>

int main()
{
	int a;
	int b;
	int c;
	
	printf("nechceme nasobky cisla: ");
	scanf("%d", &a);
	printf("skoncime pri cisle: ");
	scanf("%d", &b);
	for (c = 1; c <= b; c += 1)
	{
		if ((c % a) == 0)
		{
			continue;
		}
		if (c == b)
		{
			break;
		}
		printf("%d, ", c);
	}
	
	return 0;
}
