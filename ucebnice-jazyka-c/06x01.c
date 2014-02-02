#include <stdio.h>

int main()
{
	int c;
	FILE *f;
	
	f = fopen("06x01_ZNAKY.TXT", "w+b");
	for (c = 0; c < 256; c += 1)
	{
		putc(c, f);
	}
	
	fseek(f, 0, SEEK_SET);
	do
	{
		c = getc(f);
		switch (c)
		{
			case '0':
				printf("Byla to nula\n");
				break;
			case '1':
				printf("Byla to jednicka\n");
				break;
		}
	}
	while ((c != 'q') && (c != EOF));
	fclose(f);
	
	return 0;
}
