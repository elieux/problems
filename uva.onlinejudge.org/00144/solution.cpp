#include <string>
#include <iostream>
#include <sstream>

typedef unsigned int uint;

void solve_one(uint n_students, uint machine_max) {
	uint *queue;
	uint i;
	
	queue = new uint[n_students];
	
	// init
	for (i = 0; n_students > i; i++)
		queue[i] = i;
	queue[n_students] = 0;
	
	std::cout << n_students << " " << machine_max << " " << std::endl;
}

int main(int argc, char *argv[]) {
	uint n_students, machine_max;
	std::string line;
	std::istringstream linestream;
	
	argc = argc;
	argv = argv;
	
	std::cin.exceptions(std::iostream::badbit | std::iostream::failbit);
	linestream.exceptions(std::iostream::badbit | std::iostream::failbit);
	while (true)
	{
		getline(std::cin, line);
		linestream.clear();
		linestream.str(line);
		linestream >> n_students >> machine_max;
		
		if (0 == n_students && 0 == machine_max)
			break;
		
		solve_one(n_students, machine_max);
	}
	
	return 0;
}
