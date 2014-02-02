#include <iostream>
#include <algorithm>
#include <vector>

int main() {
	std::vector< std::pair<int, int> > maja;
	{
		int x = 0;
		int y = 0;
		
		maja.push_back(std::make_pair(x, y)); // 0
		maja.push_back(std::make_pair(x, y)); // 1
		
		int w = 2;
		while (maja.size() <= 100000)
		{
			int edge = w++ - 1;
			
			// move to (p, 0) of new circle
			++x;
			// move (-1, +1) to (0, p)
			for (int i = 0; i < edge; i++)
				maja.push_back(std::make_pair(--x, ++y));
			// move (-1, 0) to (n, p)
			for (int i = 0; i < edge; i++)
				maja.push_back(std::make_pair(--x,   y));
			// move (0, -1) to (n, 0)
			for (int i = 0; i < edge; i++)
				maja.push_back(std::make_pair(  x, --y));
			// move (+1, -1) to (0, n)
			for (int i = 0; i < edge; i++)
				maja.push_back(std::make_pair(++x, --y));
			// move (+1, 0) to (p, n)
			for (int i = 0; i < edge; i++)
				maja.push_back(std::make_pair(++x,   y));
			// move (0, +1) to (p, 0)
			for (int i = 0; i < edge; i++)
				maja.push_back(std::make_pair(  x, ++y));
		}
	}
	
	while (true)
	{
		int willi;
		std::cin >> willi;
		if (std::cin.fail())
			break;
		
		std::cout << maja[willi].first << " " << maja[willi].second << std::endl;
	}
	
	return 0;
}
