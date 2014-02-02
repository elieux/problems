#include <cstdio>

int main(int argc, char *argv[]) {
	int c;
	
	while (true)
	{
		c = getchar();
		if (c == EOF)
			break;
		
		if (c >= 32)
			c -= 7;
		
		putchar(c);
	}
	
	return 0;
}
