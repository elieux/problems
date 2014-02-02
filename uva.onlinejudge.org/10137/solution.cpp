#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cmath>

typedef unsigned int uint;

uint solve_one_using_mean(std::vector<uint> cent_amounts) {
	uint sum = 0, sum_differences = 0;
	double mean;
	
	for (std::vector<uint>::iterator i_amount = cent_amounts.begin(), end_amount = cent_amounts.end(); i_amount != end_amount; i_amount++)
		sum += (*i_amount);
	
	mean = static_cast<double>(sum) / static_cast<double>(cent_amounts.size());
	
	for (std::vector<uint>::iterator i_amount = cent_amounts.begin(), end_amount = cent_amounts.end(); i_amount != end_amount; i_amount++)
		sum_differences += static_cast<int>(floor(abs(static_cast<double>(*i_amount) - mean)));
	
	return static_cast<int>(ceil(static_cast<double>(sum_differences) / 2.0));
}

class abs_less: public std::binary_function<double, double, bool> {
	protected:
		std::less<double> less;
	
	public:
		abs_less(): less(std::less<double>()) {
		}
		
		bool operator() (double a, double b) const {
			a = abs(a);
			b = abs(b);
			
			return this->less(a, b);
		}
};

uint solve_one(std::vector<uint> amounts) {
	uint sum = 0, amount_exchanged = 0;
	std::vector<double> differences;
	double mean;
	
	for (std::vector<uint>::iterator i_amount = amounts.begin(), end_amount = amounts.end(); i_amount != end_amount; i_amount++)
		sum += (*i_amount);
	
	mean = static_cast<double>(sum) / static_cast<double>(amounts.size());
	
	for (std::vector<uint>::iterator i_amount = amounts.begin(), end_amount = amounts.end(); i_amount != end_amount; i_amount++)
		differences.push_back(static_cast<double>(*i_amount) - mean);
	
	sort(differences.begin(), differences.end(), abs_less());
	
	bool run_again = false;
	do
	{
		std::vector<double>::iterator first_positive_difference = differences.end(), first_negative_difference = differences.end();
		
		run_again = false;
		for (std::vector<double>::iterator i_difference = differences.begin(), end_difference = differences.end(); i_difference != end_difference; i_difference++)
		{
			if ((*i_difference) >= 1.0)
			{
				if (first_positive_difference == end_difference)
					first_positive_difference = i_difference;
			}
			else if (-1.0 >= (*i_difference))
			{
				if (first_negative_difference == end_difference)
					first_negative_difference = i_difference;
			}
			else // 1.0 > (*i_difference) && (*i_difference) > -1.0
			{
				differences.erase(i_difference);
				run_again = true;
				break;
			}
			
			if (first_positive_difference != end_difference && first_negative_difference != end_difference)
			{
				double transfer;
				
				if ((*first_positive_difference) > -(*first_negative_difference))
					transfer = -(*first_negative_difference);
				else if ((*first_positive_difference) < -(*first_negative_difference))
					transfer = (*first_positive_difference);
				else // (*first_positive_difference) == -(*first_negative_difference)
					transfer = (*first_positive_difference);
				
				transfer = floor(transfer);
				
				(*first_positive_difference) -= transfer;
				(*first_negative_difference) += transfer;
				amount_exchanged += static_cast<uint>(round(transfer));
				
				run_again = true;
				break;
			}
		}
	}
	while (run_again);
	
	for (std::vector<double>::iterator i_difference = differences.begin(), end_difference = differences.end(); i_difference != end_difference; i_difference++)
		amount_exchanged += static_cast<uint>(floor(abs(*i_difference)));
	
	return amount_exchanged;
}

int main(int argc, char *argv[]) {
	std::string line;
	std::istringstream linestream;
	
	argc = argc;
	argv = argv;
	
	std::cin.exceptions(std::ios_base::badbit | std::ios_base::failbit);
	linestream.exceptions(std::ios_base::badbit | std::ios_base::failbit);
	std::cout << std::setprecision(2) << std::fixed;
	while (true)
	{
		uint n_amounts;
		std::vector<uint> cent_amounts;
		
		getline(std::cin, line);
		linestream.clear();
		linestream.str(line);
		linestream >> n_amounts;
		
		if (0 == n_amounts)
			break;
		
		while (n_amounts > 0)
		{
			double dollar_amount;
			
			n_amounts--;
			
			getline(std::cin, line);
			linestream.clear();
			linestream.str(line);
			linestream >> dollar_amount;
			
			cent_amounts.push_back(static_cast<int>(round(dollar_amount * 100.0)));
		}
		
		std::cout << '$' << static_cast<double>(solve_one(cent_amounts)) / 100.0 << std::endl;
	}
	
	return 0;
}
