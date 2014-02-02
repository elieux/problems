#include <stdio.h>

int main()
{
	int a;
	int b;
	int c;
	
	a = getchar();
	b = getchar();
	c = getchar();
	
	printf("%c%c%c\n",
		((c >= 'a') && (c <= 'z')) ? (c + 'A' - 'a') : c,
		((b >= 'a') && (b <= 'z')) ? (b + 'A' - 'a') : b,
		((a >= 'a') && (a <= 'z')) ? (a + 'A' - 'a') : a);
	
	return 0;
}
