#include <iostream>

typedef unsigned int uint;

static bool debug = false;

uint solve(uint months) {
	uint nDepr, month;
	double down, value, loan, depr, payment;
	std::cin >> down >> loan >> nDepr;
	
	month = 0;
	depr = 0;
	payment = loan / static_cast<double>(months);
	value = down + loan;
	if (debug) { std::cout << "start value " << value << " loan " << loan << " depr " << depr << std::endl; }
	
	for (uint iDepr = 0; iDepr < nDepr; iDepr++)
	{
		uint deprMonth;
		double deprNew;
		
		std::cin >> deprMonth >> deprNew;
		
		for (; month < deprMonth; month++)
		{
			value *= (1.0 - depr);
			if (debug) { std::cout << "month " << month << " value " << value << " loan " << loan << " depr " << depr << std::endl; }
			
			if (loan < value)
				return month;
			
			loan -= payment;
		}
		
		depr = deprNew;
	}

	for (; month <= months; month++)
	{
		value *= (1.0 - depr);
		if (debug) { std::cout << "month " << month << " value " << value << " loan " << loan << " depr " << depr << std::endl; }
		
		if (loan < value)
			return month;
		
		loan -= payment;
	}
	
	throw std::exception();
}

int main(int argc, char *argv[]) {
	(void)argc;
	(void)argv;
	
	while (true)
	{
		int test;
		uint result;
		
		std::cin >> test;
		if (test < 0)
			break;
		
		result = solve((uint)test);
		
		std::cout << result << " month";
		if (result != 1)
			std::cout << "s";
		std::cout << std::endl;
	}
	
	return 0;
}
