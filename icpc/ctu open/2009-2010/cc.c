#include <stdio.h>
#include <string.h>

#define reset_avail() avail = {{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }}

#define DEBUG

#ifdef DEBUG
#define printfgets(msg) { printf("\tMsg: %s; Scanned: %s\n", (msg), line); counter++; if (counter > 34) { printf("\tReached counter maximum, exiting.\n"); return 1; }}
#endif

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
	const int pp[30] = { 0, 1, 2, 3, 4, 0, 0, 0, 1, 2, 3, 4, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 0, 0, 0, 1, 2, 3, 4, };
	const int pd[30] = { 1, 1, 1, 1, 1, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 0, 0, 4, 4, 4, 4, 4, };
	const char end[] = "end\n";
	
	int li, co, k;
	char line[31];
	int avail[4][10];
#ifdef DEBUG
	int counter;
	counter = 0;
#endif
	
	fgets(line, 31, stdin);
#ifdef DEBUG
	printfgets("first");
#endif
	while (strcmp(line, end) != 0)
	{
		memset(avail, 4 * 30 * sizeof(int), 1);
		
		for (li = 1; li < 7; li++)
		{
#ifdef DEBUG
			printf("\tli=%2d\n", li);
#endif
			for (co = 0; co < 31; co++)
			{
#ifdef DEBUG
				/*printf("\t\tco=%2d; k=", co);*/
#endif
				if (line[co] == '.')
					continue;
				if (!pd[co])
					continue;
				for (k = 0; k < 10; k++)
				{
#ifdef DEBUG
					/*printf("%2d,", k);*/
#endif
					if (!avail[pp[co]][k])
						continue;
					if (line[co] != digits[k][li][pp[co]])
						avail[pp[co]][k] = 0;
				}
#ifdef DEBUG
				/*printf("\n");*/
#endif
			}
			
			fgets(line, 31, stdin);
#ifdef DEBUG
			printfgets("lines");
#endif
		}
#ifdef DEBUG
		for (li = 0; li < 4; li++)
		{
			printf("\tAvail pos %d:", li);
			for (co = 0; co < 10; co++)
				printf(" %d", avail[li][co]);
			printf("\n");
		}
#endif
		
		fgets(line, 31, stdin);
#ifdef DEBUG
		printfgets("aft-1");
#endif
		fgets(line, 31, stdin);
#ifdef DEBUG
		printfgets("aft-2");
#endif
		fgets(line, 31, stdin);
#ifdef DEBUG
		printfgets("cases");
#endif
	}
	
	return 0;
}
