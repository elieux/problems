#include <iostream>
#include <vector>
#include <algorithm>

typedef unsigned int uint;

struct item {
	item *prev;
	int num;
};

struct item_num_less {
	bool operator() (const item *const a, const item *const b) {
		return a->num < b->num;
	}
};

int main() {
	std::vector<item> lis;
	while (true)
	{
		int num;
		std::cin >> num;
		if (std::cin.rdstate() & std::ios_base::eofbit)
			break;
		
		lis.push_back({ NULL, num });
	}
	
	std::vector<item *> last_of_length;
	item *best = NULL;
	for (std::vector<item>::iterator last = lis.begin(); last != lis.end(); last++)
	{
		// O(n^2)
		// for (std::vector<item>::iterator prev = lis.begin(); prev != last; prev++)
			// if ((*prev).num < (*last).num && ((*last).prev == NULL || (*last).prev->size <= (*prev).size + 1))
			// {
				// (*last).prev = &(*prev);
				// (*last).size = (*prev).size + 1;
			// }
		// if (best == NULL || best->size <= (*last).size)
			// best = &(*last);
		
		// O(nlogn)
		std::vector<item *>::iterator replace = lower_bound(last_of_length.begin(), last_of_length.end(), &(*last), item_num_less());
		if (replace != last_of_length.begin())
			(*last).prev = *(replace - 1);
		if (replace != last_of_length.end())
			*replace = &(*last);
		else
		{
			last_of_length.push_back(&(*last));
			best = &(*last);
		}
	}
	
	std::vector<int> best_seq;
	while (best != NULL)
	{
		best_seq.push_back(best->num);
		best = best->prev;
	}
	
	std::cout << best_seq.size() << std::endl;
	std::cout << "-" << std::endl;
	
	for (std::vector<int>::reverse_iterator i = best_seq.rbegin(); i != best_seq.rend(); i++)
		std::cout << (*i) << std::endl;
	
	return 0;
}
