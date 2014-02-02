#include <iostream>
#include <algorithm>
#include <vector>

typedef unsigned int uint;

struct elephant {
	uint weight;
	uint iq;
	elephant *prev;
	uint position;
};

struct elephant_is_dumber {
	bool operator() (const elephant *const a, const elephant *const b) {
		return a->iq < b->iq;
	}
	bool operator() (const elephant& a, const elephant& b) {
		return a.iq < b.iq;
	}
};

struct elephant_is_smarter {
	bool operator() (const elephant *const a, const elephant *const b) {
		return a->iq > b->iq;
	}
	bool operator() (const elephant& a, const elephant& b) {
		return a.iq > b.iq;
	}
};

struct elephant_is_bigger {
	bool operator() (const elephant& a, const elephant& b) {
		return a.weight > b.weight;
	}
	bool operator() (const elephant *const a, const elephant *const b) {
		return a->weight > b->weight;
	}
};

struct elephant_is_smaller {
	bool operator() (const elephant& a, const elephant& b) {
		return a.weight < b.weight;
	}
	bool operator() (const elephant *const a, const elephant *const b) {
		return a->weight < b->weight;
	}
};

struct elephant_is_dumber_and_bigger {
	bool operator() (const elephant& a, const elephant& b) {
		return a.weight > b.weight && a.iq < b.iq;
	}
	bool operator() (const elephant *const a, const elephant *const b) {
		return a->weight > b->weight && a->iq < b->iq;
	}
};

struct elephant_is_dumber_and_smaller {
	bool operator() (const elephant& a, const elephant& b) {
		return a.weight < b.weight && a.iq < b.iq;
	}
	bool operator() (const elephant *const a, const elephant *const b) {
		return a->weight < b->weight && a->iq < b->iq;
	}
};

struct elephant_is_smarter_and_smaller {
	bool operator() (const elephant& a, const elephant& b) {
		return a.weight < b.weight && a.iq > b.iq;
	}
	bool operator() (const elephant *const a, const elephant *const b) {
		return a->weight < b->weight && a->iq > b->iq;
	}
};

struct elephant_is_smarter_and_bigger {
	bool operator() (const elephant& a, const elephant& b) {
		return a.weight > b.weight && a.iq > b.iq;
	}
	bool operator() (const elephant *const a, const elephant *const b) {
		return a->weight > b->weight && a->iq > b->iq;
	}
};

int main() {
	std::vector<elephant> elephants;
	
	while (true)
	{
		uint weight, iq;
		std::cin >> weight >> iq;
		if (std::cin.rdstate() & std::ios_base::eofbit)
			break;
		
		elephants.push_back({ weight, iq, NULL, elephants.size() });
	}
	std::sort(elephants.begin(), elephants.end(), elephant_is_bigger());
	
	elephant *last_of_longest = NULL;
	std::vector<elephant *> last_by_length;
	for (std::vector<elephant>::iterator last = elephants.begin(); last != elephants.end(); last++)
	{
		std::vector<elephant *>::iterator replace = lower_bound(last_by_length.begin(), last_by_length.end(), &(*last), elephant_is_dumber());
		if (replace != last_by_length.begin())
			(*last).prev = *(replace - 1);
		if (replace != last_by_length.end())
			*replace = &(*last);
		else
		{
			last_by_length.push_back(&(*last));
			last_of_longest = &(*last);
		}
	}
	
	std::vector<elephant *> best_sequence;
	while (last_of_longest != NULL)
	{
		best_sequence.push_back(last_of_longest);
		last_of_longest = last_of_longest->prev;
	}
	
	std::cout << best_sequence.size() << std::endl;
	for (std::vector<elephant *>::iterator i = best_sequence.begin(); i != best_sequence.end(); i++)
		std::cout << (*i)->position + 1 << std::endl;
	
	return 0;
}
