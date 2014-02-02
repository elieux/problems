#include <iostream>

typedef unsigned int uint;

int main(int argc, char *argv[]) {
	uint n;
	
	(void)argc;
	(void)argv;
	
	std::cin >> n;
	for (uint i = 0; i < n; i++)
	{
		uint a, b, c, middle;
		std::cin >> a >> b >> c;
		
		if (a < b)
			if (b < c)
				middle = b;
			else // if (c < b)
				if (a < c)
					middle = c;
				else // if (c < a)
					middle = a;
		else // if (b < a)
			if (c < b)
				middle = b;
			else // if (b < c)
				if (a < c)
					middle = a;
				else // if (c < a)
					middle = c;
		
		std::cout << "Case " << (i + 1) << ": " << middle << std::endl;
	}
	
	return 0;
}
