#include <iostream>
#include <exception>
#include <algorithm>

typedef unsigned int uint;

int compute(int a, char op, int b) {
	switch (op) {
		case '+':
			return a + b;
		case '-':
			return a - b;
		case '*':
			return a * b;
		default:
			throw std::exception();
	}
}

int main() {
	uint nCases;
	std::cin >> nCases;
	
	for (uint iCase = 0; iCase < nCases; ++iCase)
	{
		int a, b;
		char op;
		
		std::cin >> a >> op >> b;
		std::cout << compute(a, op, b) << std::endl;
	}
	
	return 0;
}
