#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define LINE_LENGTH 256
#define MAX 20000
typedef unsigned int BitType;
typedef BitType *BitField;
#define BITS_IN_BITTYPE (sizeof(BitType) * 8)
#define BITTYPES_IN_ROW (MAX / BITS_IN_BITTYPE)
#define BYTES_IN_BITFIELD (sizeof(BitType) * MAX * BITTYPES_IN_ROW)

#define address(board, x, y) (board[(x) * BITTYPES_IN_ROW +  (y) / BITS_IN_BITTYPE])
#define bit(y) (1 << ((y) % BITS_IN_BITTYPE))
#define get(board, x, y) (address(board, x, y) & bit(y))
#define set(board, x, y) (address(board, x, y) |= bit(y))

int main(int argc, char *argv[]) {
	char line[LINE_LENGTH];
	unsigned int k, i, j, c;
	unsigned int maxX, maxY, x, y, n;
	unsigned int *board;
	
	board = (unsigned int *)malloc(BYTES_IN_BITFIELD);
	
	argc = argc; argv = argv; i = i; j = j;
	
	while (true)
	{
		fgets(line, LINE_LENGTH, stdin);
		sscanf(line, "%u %u %u", &maxX, &maxY, &n);
		if (0 == maxX && 0 == maxY && 0 == n)
			break;
		
			memset(board, 0, BYTES_IN_BITFIELD);
		
		for (k = 0; n > k; k++)
		{
			fgets(line, LINE_LENGTH, stdin);
			sscanf(line, "%u %u", &x, &y);
			
			x--;
			y--;
			
			for (i = 0; maxX > i; i++)
				set(board, i, y);
			for (j = 0; maxY > j; j++)
				set(board, x, j);
			for (i = x, j = y; maxX > i && maxY > j; i++, j++)
				set(board, i, j);
			for (i = x, j = y; maxX > i && maxY > j; i--, j--)
				set(board, i, j);
			for (i = x, j = y; maxX > i && maxY > j; i--, j++)
				set(board, i, j);
			for (i = x, j = y; maxX > i && maxY > j; i++, j--)
				set(board, i, j);
		}
		c = 0;
		for (i = 0; maxX > i; i++)
			for (j = 0; maxY > j; j++)
				if (!get(board, i, j))
					c++;
		printf("%u\n", c);
	}
	
	return 0;
}