#include <stdio.h>
#include <ctype.h>

int main()
{
	FILE *f;
	FILE *f2;
	int a;
	int c;
	int c2;
	
	f = fopen("06x02_PISMENA.TXT", "w+b");
	for (c = 0; c < 5; c += 1)
	{
		for (c2 = 0; c2 <= ('Z' - 'A'); c2 += 1)
		{
			putc(c2 + 'A', f);
			putc(c2 + 'a', f);
			putc(' ', f);
		}
		putc('\n', f);
	}
	
	fseek(f, 0, SEEK_SET);
	
	f2 = fopen("06x02_VELKY.TXT", "wb");
	
	while ((a = getc(f)) != EOF)
	{
		putchar(a);
		putc(toupper(a), f2);
	}
	
	fclose(f);
	fclose(f2);
	
	return 0;
}
