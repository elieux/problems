#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>

typedef unsigned int uint;
typedef unsigned long long int ullint;

template<typename T>
std::string convert(std::string letters, T number) {
	std::string result;
	T base = letters.size();
	
	uint zeroes = 0;
	while (number > T(zeroes))
	{
		number -= T(zeroes);
		zeroes = 0;
		
		T letter = number - T(1);
		result.push_back(letters[letter % base]);
		
		if (number % base == T(0))
			zeroes++;
		else
			zeroes = 0;
		
		number /= base;
	}
	
	std::reverse(result.begin(), result.end());
	
	return result;
}

int main() {
	uint nCases;
	std::cin >> nCases;
	
	for (uint iCase = 0; iCase < nCases; iCase++)
	{
		std::string letters;
		ullint nBoxes;
		std::cin >> letters >> nBoxes;
		
		std::cout << "Case #" << (iCase + 1) << ": " << convert(letters, nBoxes) << std::endl;
	}
	
	return 0;
}
