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
		
		uint maxValue = 0;
		for (uint beginBox = 0; beginBox <= nBoxes - nChoose; ++beginBox)
		{
			uint endBox = beginBox + nChoose;
			uint value = 0;
			for (uint iBox = beginBox; iBox < endBox; ++iBox)
				value += values[iBox];
			
			if (maxValue < value)
				maxValue = value;
		}
		
		std::cout << maxValue << std::endl;
	}
	
	return 0;
}
