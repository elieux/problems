#include <iostream>
#include <algorithm>

typedef unsigned int uint;

int main() {
	uint nCases;
	std::cin >> nCases;
	
	for (uint iCase = 0; iCase < nCases; ++iCase)
	{
		int number1, number2;
		std::cin >> number1 >> number2;
		
		char operator;
		if (number1 < number2)
			operator = '<';
		else if (number1 > number2)
			operator = '>';
		else // if (number1 == number2)
			operator = '=';
		
		std::cout << operator << std::endl;
	}
	
	return 0;
}
