#include <iostream>
#include <algorithm>

typedef unsigned int uint;

int main() {
	uint nCases;
	std::cin >> nCases;
	
	for (uint iCase = 0; iCase < nCases; ++iCase)
	{
		uint nShops;
		std::cin >> nShops;
		
		uint min, max;
		for (uint iShop = 0; iShop < nShops; ++iShop)
		{
			uint position;
			std::cin >> position;
			
			if (iShop == 0 || min > position)
				min = position;
			if (iShop == 0 || max < position)
				max = position;
		}
		
		std::cout << ((max - min) * 2) << std::endl;
	}
	
	return 0;
}
