#include <iostream>
#include <iomanip>
#include <cmath>

typedef unsigned int uint;

struct result {
	bool valid;
	double p;
	
	result(bool valid, double p):
		valid(valid),
		p(p) {
	}
};

result compute(double d, double v, double u) {
	if (u == 0.0)
		return { false, 0.0 };
	if (v == 0.0)
		return { false, 0.0 };
	if (u <= v)
		return { false, 0.0 };
	
	return { true, d / sqrt(u * u - v * v) - d / u };
}

int main() {
	uint cases;
	
	std::cout << std::fixed << std::setprecision(3);
	std::cin >> cases;
	for (uint c = 0; c < cases; c++)
	{
		double d, v, u;
		std::cin >> d >> v >> u;
		result r = compute(d, v, u);
		
		std::cout << "Case " << c + 1 << ": ";
		if (r.valid)
			std::cout << r.p;
		else
			std::cout << "can't determine";
		std::cout << std::endl;
	}
	
	return 0;
}
