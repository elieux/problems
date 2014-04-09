#include <iostream>
#include <algorithm>
#include <vector>

typedef unsigned int uint;

int main() {
	uint nCases;
	std::cin >> nCases;
	
	for (uint iCase = 0; iCase < nCases; ++iCase)
	{
		uint nBoxes, nChoose;
		std::cin >> nBoxes >> nChoose;
		
		std::vector<uint> values;
		for (uint iBox = 0; iBox < nBoxes; ++iBox)
		{
			uint value;
			std::cin >> value;
			values.push_back(value);
		}
		
		uint value = 0, maxValue = 0;
		uint firstBox = 0, lastBox = 0;
		
		for (; lastBox < nChoose; ++lastBox)
			value += values[lastBox];
		maxValue = value;
		for (; lastBox < nBoxes; firstBox++, lastBox++)
		{
			value -= values[firstBox];
			value += values[lastBox];
			
			if (maxValue < value)
				maxValue = value;
		}
		
		std::cout << maxValue << std::endl;
	}
	
	return 0;
}
