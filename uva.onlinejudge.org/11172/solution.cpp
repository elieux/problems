#include <iostream>

typedef unsigned int uint;

int main(int argc, char *argv[]) {
	uint n;
	
	(void)argc;
	(void)argv;
	
	std::cin >> n;
	for (uint i = 0; i < n; i++)
	{
		int a, b;
		std::cin >> a >> b;
		
		if (a < b)
			std::cout << "<";
		else if (a > b)
			std::cout << ">";
		else // if (a == b)
			std::cout << "=";
		std::cout << std::endl;
	}
	
	return 0;
}
