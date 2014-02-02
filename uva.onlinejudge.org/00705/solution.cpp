#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>

#define MAX_WIDTH 75
#define MAX_HEIGHT 75

#define RESERVE_FOR_STUPID_EXTRANEOUS_SPACES_AT_THE_END_OF_THE_LINE 100

#define odd(n) ((n) % 2 != 0)
#define even(n) ((n) % 2 == 0)

typedef unsigned int uint;

typedef enum { NONE, NW, SW, SE, NE } Direction;

const Direction forward[5] = { NONE, NW, SW, SE, NE };
const Direction back[5] = { NONE, SE, NE, NW, SW };

typedef struct {
	uint width;
	uint height;
	uint cycles;
	uint length;
	char slashes[MAX_HEIGHT][MAX_WIDTH + 2 + RESERVE_FOR_STUPID_EXTRANEOUS_SPACES_AT_THE_END_OF_THE_LINE];
	char squares[MAX_HEIGHT * 2][MAX_WIDTH * 2];
	
	void clear() {
		memset(this->squares, 0x00, sizeof(squares));
		this->cycles = 0;
		this->length = 0;
	}
	
	void go(const Direction go, uint& row, uint& column) const {
		switch (go) {
			case NONE:
				break;
			case NW:
				row--;
				column--;
				break;
			case SW:
				row++;
				column--;
				break;
			case SE:
				row++;
				column++;
				break;
			case NE:
				row--;
				column++;
				break;
			default:
				printf("go: %d /e Direction\n", go);
				throw "go: direction /e Direction";
		}
	}
	
	bool exists(const Direction go, uint row, uint column) const {
		switch (go) {
			case NONE:
				return even(row) != even(column) && row > 0 && column > 0 && row < this->height * 2 && column < this->width * 2;
			case NW:
			case SW:
			case SE:
			case NE:
				this->go(go, row, column);
				return this->exists(NONE, row, column);
			default:
				printf("exists: %d /e Direction\n", go);
				throw "exists: direction /e Direction";
		}
	}
	
	bool cango(const Direction go, const uint row, const uint column) const {
		switch (go) {
			case NONE:
				return true;
			case NW:
				return this->slashes[(row - 1) / 2][(column - 1) / 2] != '/';
			case SW:
				return this->slashes[(row    ) / 2][(column - 1) / 2] != '\\';
			case SE:
				return this->slashes[(row    ) / 2][(column    ) / 2] != '/';
			case NE:
				return this->slashes[(row - 1) / 2][(column    ) / 2] != '\\';
			default:
				printf("cango: %d /e Direction\n", go);
				throw "cango: direction /e Direction";
		}
	}
	
	void solve() {
		for (uint row = 0; row < this->height * 2; row++)
			for (uint column = 0; column < this->width * 2; column++)
				if (this->exists(NONE, row, column))
				{
					uint r = row, c = column, l = 0;
					Direction went = NONE;
					while (this->exists(NONE, r, c) && this->squares[r][c] == 0)
					{
						this->squares[r][c] = 1;
						l++;
						
						bool failed = true;
						for (uint i = 1; i < sizeof(forward) / sizeof(Direction); i++)
						{
							Direction go = forward[i];
							if (went != back[i] && this->exists(go, r, c) && this->cango(go, r, c))
							{
								this->go(go, r, c);
								went = go;
								failed = false;
								break;
							}
						}
						if (failed)
							break;
					}
					
					if (went != NONE && r == row && c == column)
					{
						this->cycles++;
						if (l > this->length)
							this->length = l;
					}
				}
	}
} Maze;


int main(int argc, char *argv[]) {
	argc = argc;
	argv = argv;
	
	char line[256];
	uint number = 0;
	
	while (true)
	{
		Maze maze;
		
		fgets(line, sizeof(line) / sizeof(char), stdin);
		sscanf(line, "%u %u", &maze.width, &maze.height);
		
		if (maze.width == 0 && maze.height == 0)
			break;
		
		number++;
		
		for (uint row = 0; row < maze.height; row++)
			fgets(maze.slashes[row], sizeof(maze.slashes[row]) / sizeof(char), stdin);
		
		maze.clear();
		maze.solve();
		printf("Maze #%u:\n", number);
		if (maze.cycles == 0)
			printf("There are no cycles.\n");
		else
			printf("%u Cycles; the longest has length %u.\n", maze.cycles, maze.length);
		printf("\n");
	}
	
	return 0;
}
