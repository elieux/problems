#include <stdio.h>

int main()
{
	int a;
	int c;
	int c2;
	
	for (c = 0; c < 2; c += 1)
	{
		for (c2 = 0; c2 < 4; c2 += 1)
		{
			switch (c2)
			{
				case 0:
					a = c != 0;
					printf("(%d != 0) ", c);
					break;
				case 1:
					a = c;
					printf("(%d) ", c);
					break;
				case 2:
					a = c == 0;
					printf("\n(%d == 0) ", c);
					break;
				case 3:
					a = !c;
					printf("(!%d) ", c);
					break;
			}
			if (a)
			{
				printf("je kladne\n");
			}
			else
			{
				printf("neni kladne\n");
			}
		}
		printf("\n");
	}
	
	return 0;
}
