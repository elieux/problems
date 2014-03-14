#include <iostream>

typedef unsigned int uint;

int main(int argc, char *argv[]) {
	(void)argc;
	(void)argv;
	
	std::cin.exceptions(std::ios_base::eofbit);
	
	try {
		while (true)
		{
			uint nPeople, budget, nHotels, nWeeks;
			
			std::cin >> nPeople >> budget >> nHotels >> nWeeks;
			
			
			std::cin >> x0 >> y0;
			
			for (uint i = 0; i < n; i++)
			{
				int x, y;
				std::cin >> x >> y;
				
				if (x == x0 || y == y0)
					std::cout << "divisa";
				else
				{
					bool W = x < x0;
					bool S = y < y0;
					
					if (W && S)
						std::cout << "SO";
					else if (W) // && !S
						std::cout << "NO";
					else if (S) // && !W
						std::cout << "SE";
					else // if (!W && !S)
						std::cout << "NE";
				}
				std::cout << std::endl;
			}
		}
	} catch (&std::ios_base::failure ex) {
		// end of stream
	}
	
	return 0;
}
