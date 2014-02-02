#include <stdio.h>
#include <string.h>

#undef DEBUG

int main()
{
	const char digits[10][7][6] =
	{
		{
			"+---+",
			"|   |",
			"|   |",
			"+   +",
			"|   |",
			"|   |",
			"+---+",
		},
		{
			"    +",
			"    |",
			"    |",
			"    +",
			"    |",
			"    |",
			"    +",
		},
		{
			"+---+",
			"    |",
			"    |",
			"+---+",
			"|    ",
			"|    ",
			"+---+",
		},
		{
			"+---+",
			"    |",
			"    |",
			"+---+",
			"    |",
			"    |",
			"+---+",
		},
		{
			"+   +",
			"|   |",
			"|   |",
			"+---+",
			"    |",
			"    |",
			"    +",
		},
		{
			"+---+",
			"|    ",
			"|    ",
			"+---+",
			"    |",
			"    |",
			"+---+",
		},
		{
			"+---+",
			"|    ",
			"|    ",
			"+---+",
			"|   |",
			"|   |",
			"+---+",
		},
		{
			"+---+",
			"    |",
			"    |",
			"    +",
			"    |",
			"    |",
			"    +",
		},
		{
			"+---+",
			"|   |",
			"|   |",
			"+---+",
			"|   |",
			"|   |",
			"+---+",
		},
		{
			"+---+",
			"|   |",
			"|   |",
			"+---+",
			"    |",
			"    |",
			"+---+",
		},
	};
	const char colon[7][2] =
	{
		" ",
		" ",
		"o",
		" ",
		"o",
		" ",
		" ",
	};
	const char space[7][2] =
	{
		" ",
		" ",
		" ",
		" ",
		" ",
		" ",
		" ",
	};
	
	char line[10];
	char end[] = "end\n";
	int a, b, c, d;
	int li;
#ifdef DEBUG
	int counter;
	counter = 0;
#endif
	
	fgets(line, 9, stdin);
	while(strcmp(line, end) != 0)
	{
#ifdef DEBUG
		printf("\tScanned: %s\n", line);
		counter++;
		if (counter > 10)
		{
			printf("\tReached 10 cycles, exiting.\n");
			return 1;
		}
#endif
		sscanf(line, "%d:%d", &a, &c);
#ifdef DEBUG
		printf("\ta=%d; c=%d\n", a, c);
#endif
		b = a % 10;
		a /= 10;
		d = c % 10;
		c /= 10;
#ifdef DEBUG
		printf("\ta=%d; b=%d; c=%d; d=%d\n", a, b, c, d);
#endif
		for (li = 0; li < 7; li++)
		{
			printf("%s", digits[a][li]);
			printf("%s", space[li]);
			printf("%s", space[li]);
			printf("%s", digits[b][li]);
			printf("%s", space[li]);
			printf("%s", space[li]);
			printf("%s", colon[li]);
			printf("%s", space[li]);
			printf("%s", space[li]);
			printf("%s", digits[c][li]);
			printf("%s", space[li]);
			printf("%s", space[li]);
			printf("%s\n", digits[d][li]);
		}
		
		printf("\n\n");
		fgets(line, 9, stdin);
	}
	printf("end\n");
#ifdef DEBUG
		printf("\tEnd.\n");
#endif
	
	return 0;
}
