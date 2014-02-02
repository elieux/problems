#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <string>

typedef unsigned int uint;

int main(int argc, char *argv[]) {
	(void)argc;
	(void)argv;
	
	char line[128];
	
	uint nCases;
	fgets(line, sizeof(line) / sizeof(char), stdin);
	sscanf(line, "%u", &nCases);
	
	for (uint iCase = 0; iCase < nCases; iCase++)
	{
		uint nTurtles;
		
		fgets(line, sizeof(line) / sizeof(char), stdin);
		sscanf(line, "%u", &nTurtles);
		
		std::vector<std::string> currentTurtles(nTurtles), desiredTurtles(nTurtles);
		
		for (uint iTurtle = 0; iTurtle < nTurtles; iTurtle++)
		{
			fgets(line, sizeof(line) / sizeof(char), stdin);
			const std::string turtle = std::string(line);
			
			currentTurtles[iTurtle] = turtle;
		}
		for (uint iTurtle = 0; iTurtle < nTurtles; iTurtle++)
		{
			fgets(line, sizeof(line) / sizeof(char), stdin);
			const std::string turtle = std::string(line);
			
			desiredTurtles[iTurtle] = turtle;
		}
		
		bool inserted = false;
		std::set<std::string> movedTurtles;
		for (uint riCurrentTurtle = 0, riDesiredTurtle = 0; riDesiredTurtle < nTurtles; )
		{
			const uint iCurrentTurtle = nTurtles - riCurrentTurtle - 1;
			const uint iDesiredTurtle = nTurtles - riDesiredTurtle - 1;
			const std::string desiredTurtle = desiredTurtles[iDesiredTurtle];
			
			if (!inserted && riCurrentTurtle < nTurtles && desiredTurtle == currentTurtles[iCurrentTurtle])
			{
				riCurrentTurtle++;
				riDesiredTurtle++;
				continue;
			}
			
			std::set<std::string>::iterator iMovedTurtle = movedTurtles.find(desiredTurtle);
			if (iMovedTurtle == movedTurtles.end())
			{
				movedTurtles.insert(currentTurtles[iCurrentTurtle]);
				riCurrentTurtle++;
			}
			else
			{
				movedTurtles.erase(iMovedTurtle);
				printf("%s", desiredTurtle.c_str());
				inserted = true;
				riDesiredTurtle++;
			}
		}
		printf("\n");
	}
	
	return 0;
}
