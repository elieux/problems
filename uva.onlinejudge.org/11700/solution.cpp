#include <iostream>
#include <algorithm>
#include <vector>

typedef unsigned int uint;

struct Cell {
	uint ends;
	bool north, east, south, west;
	
	Cell():
		ends(0),
		north(false),
		east(false),
		south(false),
		west(false) {
	}
	
	Cell(const uint ends):
		ends(ends),
		north(ends > 0),
		east(ends > 1),
		south(ends > 2),
		west(ends > 3) {
	}
	
	Cell(const bool north, const bool east, const bool south, const bool west):
		ends((north ? 1 : 0) + (east ? 1 : 0) + (south ? 1 : 0) + (west ? 1 : 0)),
		north(north),
		east(east),
		south(south),
		west(west) {
	}
	
	void rotate() {
		std::swap(north, east);
		std::swap(south, west);
		std::swap(east, west);
	}
};

// enum XCell { [0] = NONE, [1] = ONE, [2] = TWO, [3] = THREE, [4] = FOUR };
typedef std::vector<bool> Bits;

typedef std::vector<Cell> Row;
typedef std::vector<Row> Field;

struct Instance {
	const uint rows, cols;
	Field field;
	
	Instance(const uint rows, const uint cols):
		rows(rows),
		cols(cols),
		field(Field(rows, Row(cols))) {
	}
	
	bool solvable() {
		// return solvable_naive(0, 0);
		return solvable_quick(0, std::vector<Bits>());
	}
	
	bool solvable_quick(const uint r, std::vector<Bits> previous_rows) {
		std::vector<Bits> current_rows;
		for (uint c = 0; c < cols; ++c)
			
	}
	
	bool solvable_naive(const uint r, const uint c) {
		if (c == cols)
			return solvable_naive(r + 1, 0);
		if (r == rows)
			return true;
		
		Cell& cell = field[r][c];
		for (uint rot = 0; rot < 4; ++rot)
		{
			// std::cout << "trying " << r << "x" << c << ": " << (rot + 1) << std::endl;
			
			cell.rotate();
			if (cell.west != (c == 0 ? false : field[r][c - 1].east))
				continue;
			if (cell.north != (r == 0 ? false : field[r - 1][c].south))
				continue;
			if (c + 1 == cols && cell.east)
				continue;
			if (r + 1 == rows && cell.south)
				continue;
			
			if (solvable_naive(r, c + 1))
				return true;
		}
		
		return false;
	}
};

int main() {
	while (true)
	{
		uint rows, cols;
		std::cin >> rows >> cols;
		if (rows == 0 && cols == 0)
			return 0;
		
		Instance instance(rows, cols);
		for (Row& row: instance.field)
			for (Cell& cell: row)
			{
				std::string desc;
				std::cin >> desc;
				cell = Cell(desc[0] == 'x' ? 0 : desc.length());
			}
		
		std::cout << (instance.solvable() ? "SOLVABLE" : "UNSOLVABLE") << std::endl;
	}
}
