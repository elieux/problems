#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <string>

typedef unsigned int uint;
typedef std::map<char, const std::string> L2C;
typedef std::map<const std::string, char> C2L;
typedef std::vector<std::string> Strings;

typedef std::pair<uint, char> Choice;
typedef std::vector<Choice> Choices;
struct Choice_less {
	bool operator() (const Choice& a, const Choice& b) const {
		return a.second < b.second;
	}
};

void decode(const C2L& code2letter, std::string& encoded, const uint position, const std::string decoded, Strings& result) {
	if (result.size() >= 100)
		return;
	
	if (position == encoded.length())
		result.push_back(decoded);
	
	Choices choices;
	
	C2L::const_iterator not_found(code2letter.end());
	for (uint length = 1u; length <= std::min(static_cast<uint>(encoded.length() - position), 3u); length++)
	{
		std::string code = encoded.substr(position, length);
		C2L::const_iterator letter = code2letter.find(code);
		if (not_found != letter)
			choices.push_back(Choice(length, (*letter).second));
	}
	std::sort(choices.begin(), choices.end(), Choice_less());
	for (Choices::const_iterator it = choices.begin(); it != choices.end(); it++)
	{
		const char letter = (*it).second;
		const uint length = (*it).first;
		decode(code2letter, encoded, position + length, decoded + letter, result);
	}
}

int main() {
	uint iCase = 0;
	while (true)
	{
		uint nLetters;
		std::cin >> nLetters;
		if (nLetters == 0)
			break;
		iCase++;
		
		L2C letter2code;
		C2L code2letter;
		
		for (uint iLetter = 0; iLetter < nLetters; iLetter++)
		{
			char letter;
			std::string code;
			std::cin >> letter >> code;
			
			code2letter[code]       = letter;
			code2letter["0" + code] = letter;
		}
		
		std::string encoded;
		std::cin >> encoded;
		
		Strings result;
		
		decode(code2letter, encoded, 0, std::string(), result);
		
		std::cout << "Case #" << iCase << std::endl;
		for (Strings::const_iterator it = result.begin(); it != result.end(); it++)
			std::cout << (*it) << std::endl;
		std::cout << std::endl;
	}
	
	return 0;
}
