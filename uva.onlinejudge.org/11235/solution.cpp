#include <algorithm>
#include <iostream>
#include <vector>

typedef unsigned int uint;

struct Subseq {
	int number;
	uint start, end;
	
	Subseq():
		number(0),
		start(0),
		end(0) {
	}
	
	Subseq(int number, uint start, uint end):
		number(number),
		start(start),
		end(end) {
	}
	
	uint length() const {
		return end - start;
	}
	
	uint length(const uint startBound, const uint endBound) const {
		return std::min(endBound, end) - std::max(start, startBound);
	}
};

struct Subseq_length_less {
	uint start, end;
	
	Subseq_length_less(const uint start, const uint end):
		start(start),
		end(end) {
	}
	
	bool operator() (const Subseq& a, const Subseq& b) const {
		return a.length(start, end) < b.length(start, end);
	}
};

struct Subseq_start_less {
	bool operator() (const Subseq& a, const Subseq& b) const {
		return a.start < b.start;
	}
	
	bool operator() (const Subseq& a, const uint b) const {
		return a.start < b;
	}
	
	bool operator() (const uint a, const Subseq& b) const {
		return a < b.start;
	}
};

struct Subseq_end_less {
	bool operator() (const Subseq& a, const Subseq& b) const {
		return a.end < b.end;
	}
	
	bool operator() (const Subseq& a, const uint b) const {
		return a.end < b;
	}
	
	bool operator() (const uint a, const Subseq& b) const {
		return a < b.end;
	}
};

uint solve(const std::vector<Subseq>& subseqs, const uint start, const uint end) {
	uint bestLength = 0;
	
	std::vector<Subseq>::const_iterator itSubseq = subseqs.begin();
	while (itSubseq != subseqs.end() && (*itSubseq).end < start)
		itSubseq++;
	while (itSubseq != subseqs.end() && (*itSubseq).start < end)
	{
		const uint length = (*itSubseq).length(start, end);
		if (bestLength < length)
			bestLength = length;
		itSubseq++;
	}
	
	return bestLength;
}

uint solve_log(const std::vector<Subseq>& subseqs, const uint start, const uint end) {
	if (start == end)
		return 0;
	
	std::vector<Subseq>::const_iterator beginSubseq = subseqs.begin(), endSubseq = subseqs.end();
	beginSubseq = std::lower_bound(beginSubseq, endSubseq, start, Subseq_end_less()  );
	endSubseq   = std::upper_bound(beginSubseq, endSubseq, end,   Subseq_start_less());
	
	if (beginSubseq == endSubseq)
		return 0;
	
	const Subseq& result = *std::max_element(beginSubseq, endSubseq, Subseq_length_less(start, end));
	return result.length(start, end);
}

// uint solve_precomputed(const std::vector<Subseq>& subseqs, const std::vector< std::vector<uint> >& maxima, const uint start, const uint end) {
	// uint bestLength = 0;
	
	// std::vector<Subseq>::const_iterator beginSubseq = subseqs.begin(), endSubseq = subseqs.end();
	// std::lower_bound(beginSubseq, endSubseq, start, Subseq_start_less());
	// return bestLength;
// }

void precompute(const std::vector<Subseq>& subseqs, std::vector< std::vector<uint> >& maxima) {
	maxima.resize(subseqs.size());
	
	uint lookahead = 1, iLookahead = 0;
	while (lookahead <= subseqs.size())
	{
		if (iLookahead == 0)
			for (uint iSubseq = 0; iSubseq < subseqs.size(); iSubseq++)
				maxima[iSubseq].push_back(iSubseq);
		else
			for (uint iSubseq = 0; iSubseq + lookahead - 1 < subseqs.size(); iSubseq++)
			{
				const uint left = maxima[iSubseq][iLookahead - 1];
				const uint right = maxima[iSubseq + (lookahead >> 1)][iLookahead - 1];
				maxima[iSubseq][iLookahead] = subseqs[left].length() < subseqs[right].length() ? left : right;
			}
		
		lookahead <<= 1;
		iLookahead++;
	}
}

int main() {
	while (true)
	{
		uint nNumbers, nQueries;
		std::cin >> nNumbers;
		if (nNumbers == 0)
			break;
		std::cin >> nQueries;
		
		std::vector<Subseq> subseqs;
		{
			Subseq subseq;
			uint iNumber = 0;
			
			subseq.start = iNumber;
			std::cin >> subseq.number;
			iNumber++;
			
			for (; iNumber < nNumbers; iNumber++)
			{
				int number;
				std::cin >> number;
				if (number != subseq.number)
				{
					subseq.end = iNumber;
					subseqs.push_back(subseq);
					subseq = Subseq(number, iNumber, 0);
				}
			}
			
			subseq.end = iNumber;
			subseqs.push_back(subseq);
		}
		
		// std::vector< std::vector<uint> > maxima;
		// precompute(subseqs, maxima);
		
		for (uint iQuery = 0; iQuery < nQueries; iQuery++)
		{
			uint start, end;
			std::cin >> start >> end;
			start--; // convert from 1-indexed [start, end] to 0-indexed [start, end)
			
			// std::cout << solve(subseqs, start, end) << std::endl;
			std::cout << solve_log(subseqs, start, end) << std::endl;
			// std::cout << solve_precomputed(subseqs, maxima, start, end) << std::endl;
		}
	}
	
	return 0;
}
