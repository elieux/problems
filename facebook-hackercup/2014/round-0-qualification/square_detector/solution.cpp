#include <iostream>
#include <algorithm>
#include <limits>

typedef unsigned int uint;

enum class State { INIT, topbegin_FOUND, TOPRIGHT_FOUND, FAILED };

int main() {
	uint nCases;
	std::cin >> nCases;
	
	for (uint iCase = 0; iCase < nCases; iCase++)
	{
		uint length;
		std::cin >> length;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		char matrix[25][25];
		
		for (uint r = 0; r < length; r++)
			std::cin >> matrix[r];
		
		State state = State::INIT;
		uint r_top, c_topbegin, c_topend;
		
		for (uint r = 0; r < length; r++)
			for (uint c = 0; c < length; c++)
				switch (state) {
					case State::INIT:
						if (matrix[r][c] == '#')
						{
							r_top = r;
							c_topbegin = c;
							state = State::topbegin_FOUND;
						}
						break;
					case State::topbegin_FOUND:
						if (matrix[r][c] == '.' || r_top != r)
						{
							c_topend = r_top == r ? c : length;
							state = State::TOPRIGHT_FOUND;
						}
						break;
					case State::TOPRIGHT_FOUND: {
						bool r_inside =     r_top <= r && r < r_top + (c_topend - c_topbegin);
						bool c_inside = c_topbegin <= c && c < c_topend;
						bool   inside = r_inside && c_inside;
						if (inside && matrix[r][c] == '.')
							state = State::FAILED;
						if (!inside && matrix[r][c] == '#')
							state = State::FAILED;
						break;
					}
					case State::FAILED:
						break;
				}
		std::cout << "Case #" << (iCase + 1) << ": " << (state != State::FAILED ? "YES" : "NO") << std::endl;
	}
	
	return 0;
}
