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
		((a >= 'A') && (a <= 'Z')) ? (a + 'a' - 'A') : a,
		((b >= 'A') && (b <= 'Z')) ? (b + 'a' - 'A') : b,
		((c >= 'A') && (c <= 'Z')) ? (c + 'a' - 'A') : c);
	
	return 0;
}
