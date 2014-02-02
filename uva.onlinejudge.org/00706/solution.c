#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define BUF_LEN 32
#define NUM_LEN 16

#define SEGMENTS 7
typedef enum { TOP, TOPLEFT, TOPRIGHT, MIDDLE, BOTTOMLEFT, BOTTOMRIGHT, BOTTOM } segment;

#define to_digit(x) ((unsigned int)((x) - '0'))

int main(int argc, char *argv[]) {
	unsigned int size;
	char number[NUM_LEN];
	char line[BUF_LEN];
	char character;
	unsigned int i, j, iNumber, length, rows, columns, part, seg;
	
	bool digits[10][SEGMENTS] = {
		{ true,	true,	true,	false,	true,	true,	true },
		{ false,	false,	true,	false,	false,	true,	false },
		{ true,	false,	true,	true,	true,	false,	true },
		{ true,	false,	true,	true,	false,	true,	true },
		{ false,	true,	true,	true,	false,	true,	false },
		{ true,	true,	false,	true,	false,	true,	true },
		{ true,	true,	false,	true,	true,	true,	true },
		{ true,	false,	true,	false,	false,	true,	false },
		{ true,	true,	true,	true,	true,	true,	true },
		{ true,	true,	true,	true,	false,	true,	true }
	};
	
	while (NULL != fgets(line, BUF_LEN, stdin))
	{
		sscanf(line, "%u %s", &size, number);
		if (0 == size)
			break;
		rows = 3 + 2 * size;
		columns = 2 + size;
		length = strlen(number);
		
		for (i = 0; i < rows; i++)
		{
			if (0 == i)
				part = 1;
			else if (1 + size == i)
				part = 3;
			else if (2 + 2 * size == i)
				part = 5;
			else if (1 + size > i)
				part = 2;
			else if (1 + size < i)
				part = 4;
			for (iNumber = 0; iNumber < length; iNumber++)
			{
				if (iNumber > 0)
					putchar(' ');
				switch (part) {
					case 1:
					case 3:
					case 5:
						putchar(' ');
						seg = 1 == part ? TOP : (3 == part ? MIDDLE : BOTTOM);
						character = digits[to_digit(number[iNumber])][seg] ? '-' : ' ';
						for (j = 0; j < size; j++)
							putchar(character);
						putchar(' ');
						break;
					case 2:
					case 4:
						seg = 2 == part ? TOPLEFT : BOTTOMLEFT;
						character = digits[to_digit(number[iNumber])][seg] ? '|' : ' ';;
						putchar(character);
						for (j = 0; j < size; j++)
							putchar(' ');
						seg = 2 == part ? TOPRIGHT : BOTTOMRIGHT;
						character = digits[to_digit(number[iNumber])][seg] ? '|' : ' ';;
						putchar(character);
						break;
				}
			}
			printf("\n");
		}
		
		printf("\n");
	}
	
	return 0;
}
