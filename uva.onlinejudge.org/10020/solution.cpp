#include <iostream>
#include <algorithm>
#include <vector>

typedef unsigned int uint;

struct line {
	int l, r;
};

typedef std::vector<const line *> segments;

struct line_less_lr {
	bool operator() (const line& a, const line& b) {
		return (a.l == b.l) ? (a.r < b.r) : (a.l < b.l);
	}
	bool operator() (const line * const a, const line * const b) {
		return (a->l == b->l) ? (a->r < b->r) : (a->l < b->l);
	}
};

struct line_less_rl {
	bool operator() (const line& a, const line &b) {
		return (a.r == b.r) ? (a.l < b.l) : (a.r < b.r);
	}
	bool operator() (const line * const a, const line * const b) {
		return (a->r == b->r) ? (a->l < b->l) : (a->r < b->r);
	}
};

void solve(const segments& segments_lr, const segments& segments_rl, const line& target) {
	segments cover;
	
	segments::const_iterator
		i_lr = segments_lr.begin(),
		e_lr = segments_lr.end();
	segments::const_reverse_iterator
		ir_rl = segments_rl.rbegin(),
		er_rl = segments_rl.rend();
	
	if ((*i_lr)->l <= target.l && target.r <= (*ir_rl)->r)
	{
		int last_end = target.l;
		while (i_lr != e_lr && last_end < target.r)
		{
			const line *best = NULL;
			while (i_lr != e_lr && (*i_lr)->l <= last_end)
			{
				const line * const candidate = *i_lr++;
				if (best == NULL || candidate->r > best->r)
					best = candidate;
			}
			if (best == NULL)
			{
				std::cout << "0" << std::endl;
				return;
			}
			cover.push_back(best);
			last_end = best->r;
		}
	}
	
	std::sort(cover.begin(), cover.end(), line_less_lr());
	std::cout << cover.size() << std::endl;
	for (segments::iterator it = cover.begin(); it != cover.end(); it++)
		std::cout << (*it)->l << " " << (*it)->r << std::endl;
}

int main() {
	uint cases;
	
	std::cin >> cases;
	for (uint c = 0; c < cases; c++)
	{
		if (c > 0)
			std::cout << std::endl;
		
		line target;
		target.l = 0;
		std::cin >> target.r;
		
		segments segments_lr, segments_rl;
		while (true)
		{
			line *segment = new line();
			std::cin >> segment->l >> segment->r;
			if (segment->l == 0 && segment->r == 0)
				break;
			
			segments_lr.push_back(segment);
			segments_rl.push_back(segment);
		}
		std::sort(segments_lr.begin(), segments_lr.end(), line_less_lr());
		std::sort(segments_rl.begin(), segments_rl.end(), line_less_rl());
		
		solve(segments_lr, segments_rl, target);
		
		for (segments::iterator it = segments_lr.begin(); it != segments_lr.end(); it++)
			delete *it;
	}
}