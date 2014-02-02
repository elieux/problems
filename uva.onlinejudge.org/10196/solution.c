#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define PIECES 8

#define MOVES 5
typedef enum { M_DIAGONAL = 0, M_STRAIGHT, M_LSHAPED, M_IMMEDIATE, M_FORWARDIMMEDIATEDIAGONAL } Move;

#define COLORS 2
typedef enum { C_WHITE = 0, C_BLACK } Color;

#define LINE_LEN 16

#define BOARD_HEIGHT 8
#define BOARD_WIDTH 8
typedef char Board[BOARD_HEIGHT][BOARD_WIDTH];
#define isValidCoordinates(x,y) (BOARD_WIDTH > (x) && BOARD_HEIGHT > (y))

#define checkCheck(x,y) \
	if (NULL != strchr(moves[attackerColor][i], board[y][x])) \
		return true
bool isCheck(Board board, Color attackerColor, unsigned int kingX, unsigned int kingY) {
	static const char moves[COLORS][MOVES][PIECES] = {{
		"QB",
		"QR",
		"N",
		"K",
		"P"},{
		"qb",
		"qr",
		"n",
		"k",
		"p"}};
	unsigned int i, x, y;
	
	for (i = 0; i < MOVES; i++)
		switch (i) {
			case M_DIAGONAL:
				for (x = kingX + 1, y = kingY + 1; isValidCoordinates(x, y); x++, y++)
				{
					checkCheck(x, y);
					if ('.' != board[y][x])
						break;
				}
				for (x = kingX - 1, y = kingY + 1; isValidCoordinates(x, y); x--, y++)
				{
					checkCheck(x, y);
					if ('.' != board[y][x])
						break;
				}
				for (x = kingX + 1, y = kingY - 1; isValidCoordinates(x, y); x++, y--)
				{
					checkCheck(x, y);
					if ('.' != board[y][x])
						break;
				}
				for (x = kingX - 1, y = kingY - 1; isValidCoordinates(x, y); x--, y--)
				{
					checkCheck(x, y);
					if ('.' != board[y][x])
						break;
				}
				break;
			case M_STRAIGHT:
				for (x = kingX + 1; isValidCoordinates(x, kingY); x++)
				{
					checkCheck(x, kingY);
					if ('.' != board[kingY][x])
						break;
				}
				for (x = kingX - 1; isValidCoordinates(x, kingY); x--)
				{
					checkCheck(x, kingY);
					if ('.' != board[kingY][x])
						break;
				}
				for (y = kingY + 1; isValidCoordinates(kingX, y); y++)
				{
					checkCheck(kingX, y);
					if ('.' != board[y][kingX])
						break;
				}
				for (y = kingY - 1; isValidCoordinates(kingX, y); y--)
				{
					checkCheck(kingX, y);
					if ('.' != board[y][kingX])
						break;
				}
				break;
			case M_LSHAPED:
				if (isValidCoordinates(kingX + 2, kingY + 1))
					checkCheck(kingX + 2, kingY + 1);
				if (isValidCoordinates(kingX + 2, kingY - 1))
					checkCheck(kingX + 2, kingY - 1);
				if (isValidCoordinates(kingX - 2, kingY + 1))
					checkCheck(kingX - 2, kingY + 1);
				if (isValidCoordinates(kingX - 2, kingY - 1))
					checkCheck(kingX - 2, kingY - 1);
				if (isValidCoordinates(kingX + 1, kingY + 2))
					checkCheck(kingX + 1, kingY + 2);
				if (isValidCoordinates(kingX + 1, kingY - 2))
					checkCheck(kingX + 1, kingY - 2);
				if (isValidCoordinates(kingX - 1, kingY + 2))
					checkCheck(kingX - 1, kingY + 2);
				if (isValidCoordinates(kingX - 1, kingY - 2))
					checkCheck(kingX - 1, kingY - 2);
				break;
			case M_IMMEDIATE:
				/* cannot happen */
				break;
			case M_FORWARDIMMEDIATEDIAGONAL:
				switch (attackerColor) {
					case C_WHITE:
						if (isValidCoordinates(kingX + 1, kingY + 1))
							checkCheck(kingX + 1, kingY + 1);
						if (isValidCoordinates(kingX - 1, kingY + 1))
							checkCheck(kingX - 1, kingY + 1);
						break;
					case C_BLACK:
						if (isValidCoordinates(kingX + 1, kingY - 1))
							checkCheck(kingX + 1, kingY - 1);
						if (isValidCoordinates(kingX - 1, kingY - 1))
							checkCheck(kingX - 1, kingY - 1);
						break;
				}
				break;
		}
	return false;
}

int main(int argc, char *argv[]) {
	char line[LINE_LEN];
	unsigned int i, j, k;
	unsigned int blackKingX, blackKingY;
	unsigned int whiteKingX, whiteKingY;
	bool empty;
	Board board;
	
	i = 0;
	while (true)
	{
		i++;
		
		whiteKingX = BOARD_WIDTH;
		whiteKingY = BOARD_HEIGHT;
		blackKingX = BOARD_WIDTH;
		blackKingY = BOARD_HEIGHT;
		empty = true;
		
		if (1 < i)
			fgets(line, LINE_LEN, stdin);
		for (j = 0; j < BOARD_HEIGHT; j++)
		{
			fgets(line, LINE_LEN, stdin);
			for (k = 0; k < BOARD_WIDTH; k++)
			{
				board[j][k] = line[k];
				if ('k' == line[k])
				{
					blackKingX = k;
					blackKingY = j;
				}
				if ('K' == line[k])
				{
					whiteKingX = k;
					whiteKingY = j;
				}
				if (empty && '.' != line[k])
					empty = false;
			}
		}
		if (empty)
			break;
		printf("Game #%d: ", i);
		
		if (isCheck(board, C_WHITE, blackKingX, blackKingY))
			printf("black");
		else if (isCheck(board, C_BLACK, whiteKingX, whiteKingY))
			printf("white");
		else
			printf("no");
		
		printf(" king is in check.\n");
		
	}
	
	return 0;
}
