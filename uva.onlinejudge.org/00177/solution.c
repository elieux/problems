#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define FOLDS 13
#define SIZE 512
#define PIECES 8192

#define makeminmax(min, max, value) do { if ((value) < (min)) { (min) = (value); } if ((value) > (max)) { (max) = (value); } } while (false)

typedef unsigned int uint;

typedef enum { UP, DOWN, LEFT, RIGHT } direction;

direction rotate[] = { [UP] = LEFT, [DOWN] = RIGHT, [LEFT] = DOWN, [RIGHT] = UP };

int main(int argc, char *argv[]) {
	char canvas[SIZE][SIZE];
	direction pieces[PIECES];
	
	(void)argc;
	(void)argv;
	
	{
		uint fold, piece;
		uint lastpiece = 0;
		
		pieces[lastpiece] = RIGHT;
		for (fold = 1; fold <= FOLDS; fold++)
		{
			
			for (piece = 0; piece <= lastpiece; piece++)
				pieces[lastpiece + 1 + piece] = rotate[pieces[lastpiece - piece]];
			lastpiece += lastpiece + 1;
		}
	}
	
	while (true)
	{
		uint folds;
		
		scanf("%u", &folds);
		if (0 == folds)
			break;
		
		memset(canvas, ' ', sizeof(canvas));
		
		{
			uint row = SIZE / 2;
			uint column = SIZE / 2;
			uint top = SIZE;
			uint bottom = 0;
			uint left = SIZE;
			uint right = 0;
			uint piece, lastpiece;
			
			for (piece = 0, lastpiece = pow(2, folds) - 1; piece <= lastpiece; piece++)
			{
				switch (pieces[piece]) {
					case UP:
						break;
					case DOWN:
						row++;
						break;
					case LEFT:
						column--;
						break;
					case RIGHT:
						column++;
						break;
				}
				
				makeminmax(top, bottom, row);
				makeminmax(left, right, column);
				switch (pieces[piece]) {
					case UP:
					case DOWN:
						canvas[row][column] = '|';
						break;
					case LEFT:
					case RIGHT:
						canvas[row][column] = '_';
						break;
				}
				
				switch (pieces[piece]) {
					case UP:
						row--;
						break;
					case DOWN:
						break;
					case LEFT:
						column--;
						break;
					case RIGHT:
						column++;
						break;
				}
			}
			
			for (row = top; row <= bottom; row++)
			{
				uint last;
				
				for (column = right; column >= left; column--)
					if (canvas[row][column] != ' ')
					{
						last = column;
						break;
					}
				
				canvas[row][last + 1] = '\0';
				printf("%s\n", &(canvas[row][left]));
			}
			printf("^\n");
		}
	}
	
	return 0;
}
