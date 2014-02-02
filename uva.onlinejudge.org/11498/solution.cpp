#include <iostream>

typedef unsigned int uint;

int main(int argc, char *argv[]) {
	(void)argc;
	(void)argv;
	
	while (true)
	{
		uint n;
		int x0, y0;
		
		std::cin >> n;
		if (n == 0)
			break;
		
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
	
	return 0;
}
