#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

typedef unsigned int uint;

uint pop(std::multiset<uint, std::greater<uint> >& set) {
	std::multiset<uint, std::greater<uint> >::iterator it = set.end();
	it--;
	uint result = (*it);
	set.erase(it);
	return result;
}

int main() {
	while (true)
	{
		uint nNumbers;
		std::cin >> nNumbers;
		if (nNumbers == 0)
			break;
		
		std::multiset<uint, std::greater<uint> > nums;
		{
			std::vector<uint> numbers;
			for (uint iNumber = 0; iNumber < nNumbers; iNumber++)
			{
				uint number;
				std::cin >> number;
				numbers.push_back(number);
			}
			std::sort(numbers.begin(), numbers.end(), std::greater<uint>());
			nums.insert(numbers.begin(), numbers.end());
		}
		
		uint cost = 0;
		while (nums.size() > 1)
		{
			uint sum = 0;
			sum += pop(nums);
			sum += pop(nums);
			
			nums.insert(sum);
			cost += sum;
		}
				
		std::cout << cost << std::endl;
	}
	
	return 0;
}
