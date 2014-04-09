#include <iostream>
#include <algorithm>
#include <utility>

typedef unsigned int uint;
typedef std::pair<uint, uint> uint_pair;

uint diff(const uint a, const uint b) {
	return a < b ? b - a : a - b;
}

int main() {
	while (true)
	{
		uint_pair size, start, target;
		std::cin >> size.first >> size.second >> start.first >> start.second >> target.first >> target.second;
		if (std::cin.fail())
			break;
		
		uint_pair distance = { diff(start.first, target.first), diff(start.second, target.second) };
		uint_pair minmax = std::minmax(distance.first, distance.second);
		
		uint steps_diagonal = minmax.first;
		uint steps_straight = minmax.second - minmax.first;
		
		std::cout << (steps_diagonal + steps_straight) << std::endl;
	}
	
	return 0;
}
