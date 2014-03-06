#include <iostream>
#include <algorithm>

typedef unsigned int uint;

int main() {
	uint nCases;
	std::cin >> nCases;
	for (uint iCase = 0; iCase < nCases; ++iCase)
	{
		uint nRunners;
		std::cin >> nRunners;
		
		uint maxSpeed = 0;
		for (uint iRunner = 0; iRunner < nRunners; ++iRunner)
		{
			uint speed;
			std::cin >> speed;
			if (maxSpeed < speed)
				maxSpeed = speed;
		}
		
		std::cout << "Case " << (iCase + 1) << ": " << maxSpeed << std::endl;
	}
	
	return 0;
}
