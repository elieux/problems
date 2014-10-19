#include <iostream>
#include <algorithm>
#include <set>
#include <string>

typedef unsigned int uint;
typedef unsigned long long int ullint;

template <typename T>
T factorial(const T num) {
	T result(1);
	for (T i(1); i <= num; ++i)
		result *= i;
	return result;
}

template <typename T>
std::string permute(std::string word, T n) {
	std::multiset<char> letters(word.begin(), word.end());
	
	T len(letters.size());
	std::string result;
	T fact(factorial(len));
	
	for (T i(len); i > 0; --i)
	{
		fact /= i;
		auto letter = letters.begin();
		std::advance(letter, n / fact);
		n %= fact;
		
		result.push_back(*letter);
		letters.erase(letter);
	}
	result.push_back(*letters.begin());
	
	return result;
}

int main() {
	uint nCases;
	std::cin >> nCases;
	
	for (uint iCase = 0; iCase < nCases; ++iCase)
	{
		std::string word;
		ullint n;
		
		std::cin >> word >> n;
		std::cout << permute(word, n) << std::endl;
	}
	
	return 0;
}
