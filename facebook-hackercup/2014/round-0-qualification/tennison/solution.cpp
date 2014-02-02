#include <iostream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <cmath>

typedef unsigned int uint;
typedef unsigned long long int ullint;

struct Problem {
	typedef std::map<double, double> GlobalMemo;
	typedef std::map<uint, double> Memo;
	
	static GlobalMemo global_memo;
	
	static double merge(double probability, double resultTrue, double resultFalse) {
		return probability * resultTrue + (1.0 - probability) * resultFalse;
	}
	
	uint nMatchesToWin, nMatchesWon, nMatchesLost;
	double pWinWhenSun, pWinWhenRain, pSun, sunPlusWhenWin, pSunPlusWhenWin, sunMinusWhenLose, pSunMinusWhenLose;
	Memo memo;
	
	Problem():
		nMatchesWon(0),
		nMatchesLost(0),
		memo(Memo()) {
	}
	
	Memo::key_type hash() const {
		uint hash = 0;
		hash *= 100;
		hash += nMatchesWon;
		hash *= 100;
		hash += nMatchesLost;
		hash *= 1001;
		hash += 1000.0 * pSun;
		return hash;
	}
	
	GlobalMemo::key_type unique_hash() const { // overflows
		GlobalMemo::key_type hash = 0;
		hash *= 100;
		hash += nMatchesToWin;
		hash *= 100;
		hash += nMatchesWon;
		hash *= 100;
		hash += nMatchesLost;
		hash *= 1001;
		hash += 1000.0 * pSun;
		hash *= 1001;
		hash += 1000.0 * pWinWhenSun;
		hash *= 1001;
		hash += 1000.0 * pWinWhenRain;
		hash *= 1001;
		hash += 1000.0 * sunPlusWhenWin;
		hash *= 1001;
		hash += 1000.0 * pSunPlusWhenWin;
		hash *= 1001;
		hash += 1000.0 * sunMinusWhenLose;
		hash *= 1001;
		hash += 1000.0 * pSunMinusWhenLose;
		return hash;
	}
	
	void changePSun(bool win) {
		pSun += win ? sunPlusWhenWin : -sunMinusWhenLose;
		pSun = std::max(0.0, std::min(1.0, pSun));
	}
	
	double pWin() {
		if (nMatchesToWin == nMatchesWon)
			return 1.0;
		if (nMatchesToWin == nMatchesLost)
			return 0.0;
		
		auto memoresult = memo.find(hash());
		if (memo.end() != memoresult)
			return (*memoresult).second;
		
		double thisPSun = pSun;
		double result = 0.0;
		
		nMatchesWon++;
		{
			result += merge(thisPSun,
				pWinWhenSun  * (1.0 - pSunPlusWhenWin) * pWin(),
				pWinWhenRain * (1.0 - pSunPlusWhenWin) * pWin());
			
			changePSun(true);
			{
				result += merge(thisPSun,
					pWinWhenSun  * pSunPlusWhenWin * pWin(),
					pWinWhenRain * pSunPlusWhenWin * pWin());
			}
			pSun = thisPSun;
		}
		nMatchesWon--;
		
		nMatchesLost++;
		{
			result += merge(thisPSun,
				(1.0 - pWinWhenSun)  * (1.0 - pSunMinusWhenLose) * pWin(),
				(1.0 - pWinWhenRain) * (1.0 - pSunMinusWhenLose) * pWin());
			
			changePSun(false);
			{
				result += merge(thisPSun,
					(1.0 - pWinWhenSun)  * pSunMinusWhenLose * pWin(),
					(1.0 - pWinWhenRain) * pSunMinusWhenLose * pWin());
			}
			pSun = thisPSun;
		}
		nMatchesLost--;
		
		memo.insert(std::make_pair(hash(), result));
		return result;
	}
	
	double pWin_objects() const {
		if (nMatchesToWin == nMatchesWon)
			return 1.0;
		if (nMatchesToWin == nMatchesLost)
			return 0.0;
		
		auto memoresult = global_memo.find(unique_hash());
		if (global_memo.end() != memoresult)
			return (*memoresult).second;
		
		Problem whenWon(*this), whenLost(*this);
		whenWon.nMatchesWon++;
		whenLost.nMatchesLost++;
		
		Problem whenWonAndSunPlus(whenWon);
		whenWonAndSunPlus.changePSun(true);
		
		Problem whenLostAndSunMins(whenLost);
		whenLostAndSunMins.changePSun(false);
		
		double pWinWhenWin  = merge(pSunPlusWhenWin,   whenWonAndSunPlus.pWin_objects(),  whenWon.pWin_objects());
		double pWinWhenLose = merge(pSunMinusWhenLose, whenLostAndSunMins.pWin_objects(), whenLost.pWin_objects());
		double pWin = 
			merge(pSun,
				merge(pWinWhenSun,  pWinWhenWin, pWinWhenLose),
				merge(pWinWhenRain, pWinWhenWin, pWinWhenLose));
		
		global_memo.insert(std::make_pair(unique_hash(), pWin));
		return pWin;
	}
	
	double pWin2() const { // wrong results
		if (nMatchesToWin == nMatchesWon)
			return 1.0;
		if (nMatchesToWin == nMatchesLost)
			return 0.0;
		
		double pWin = 0.0;
		for (uint nMatchesWillLose = 0; nMatchesWillLose < nMatchesToWin - nMatchesLost; nMatchesWillLose++)
			pWin += pow((1.0 - pSunPlusWhenWin) * merge(pSun, pWinWhenSun, pWinWhenRain), nMatchesToWin - nMatchesWon) * pow((1.0 - pSunMinusWhenLose) * merge(pSun, 1.0 - pWinWhenSun, 1.0 - pWinWhenRain), nMatchesWillLose);
		
		Problem whenWonAndSunPlus(*this);
		whenWonAndSunPlus.nMatchesWon++;
		whenWonAndSunPlus.changePSun(true);
		
		Problem whenLostAndSunMins(*this);
		whenLostAndSunMins.nMatchesLost++;
		whenLostAndSunMins.changePSun(false);
		
		pWin += pSun * pWinWhenSun         * pSunPlusWhenWin   * whenWonAndSunPlus.pWin2();
		pWin += pSun * (1.0 - pWinWhenSun) * pSunMinusWhenLose * whenLostAndSunMins.pWin2();
		
		return pWin;
	}
};

Problem::GlobalMemo Problem::global_memo = Problem::GlobalMemo();

int main() {
	uint nCases;
	std::cin >> nCases;
	
	std::cout << std::fixed << std::setprecision(6);
	for (uint iCase = 0; iCase < nCases; iCase++)
	{
		Problem p;
		std::cin >> p.nMatchesToWin;
		std::cin >> p.pWinWhenSun >> p.pWinWhenRain >> p.pSun >> p.sunPlusWhenWin >> p.pSunPlusWhenWin >> p.sunMinusWhenLose >> p.pSunMinusWhenLose;
		std::cout << "Case #" << (iCase + 1) << ": " << p.pWin_objects() << std::endl;
	}
	
	return 0;
}
