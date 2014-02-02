#include <cstdio>
#include <climits>
#include <cstring>
#include <map>
#include <vector>
#include <string>

typedef unsigned int uint;

class Road;
class City;
class Map;

class Road {
	public:
		std::string name;
		uint length;
		uint city1, city2;
		
		Road(std::string name, uint length, uint city1, uint city2):
			name(name), length(length), city1(city1), city2(city2) {
		}
};

class Path {
	public:
		uint length;
		std::vector<Road *> roads;
		
		Path():
			length(USHRT_MAX + 1) {
		}
};

class Map {
	public:
		std::vector<std::string> cities;
		std::map<std::string, uint> citiesR;
		Road *roads[100][100];
		std::map<uint, Path *> pathCache;
		
		Map() {
			memset(this->roads, 0x00, sizeof(this->roads));
		}
		
		Path *findShortest(uint ct1, uint ct2, int k) {
			uint base = 256;
			uint key = ct1 * base * base + ct2 * base + k;
			
			if (0 == this->pathCache.count(key))
				this->pathCache[key] = this->computeShortest(ct1, ct2, k);
			
			return this->pathCache[key];
		}
		
		Path *computeShortest(uint ct1, uint ct2, int k) {
			if (-1 == k)
			{
				Path *path = new Path();
				
				if (NULL != this->roads[ct1][ct2])
				{
					path->length = this->roads[ct1][ct2]->length;
					path->roads.push_back(this->roads[ct1][ct2]);
				}
				
				return path;
			}
			else
			{
				Path *p1 = this->findShortest(ct1, ct2, k - 1);
				Path *p2 = this->findShortest(ct1, k, k - 1);
				Path *p3 = this->findShortest(k, ct2, k - 1);
				
				if (p1->length <= p2->length + p3->length)
					return p1;
				else
				{
					Path *path = new Path();
					
					path->length = p2->length + p3->length;
					path->roads.insert(path->roads.end(), p2->roads.begin(), p2->roads.end());
					path->roads.insert(path->roads.end(), p3->roads.begin(), p3->roads.end());
					
					return path;
				}
			}
		}
		
		void solve(char line[1024]) {
			std::string city1, city2;
			
			for (char *i = line, *start = line; *i != '\0'; i++)
				switch (*i) {
					case ',':
						city1 = std::string(start, i - start);
						start = i + 1;
						break;
					case '\n':
						city2 = std::string(start, i - start);
						
						uint ct1 = this->citiesR[city1];
						uint ct2 = this->citiesR[city2];
						
						Path *path = this->findShortest(ct1, ct2, (int)this->cities.size());
						
						city2 = city1;
						
						printf("\n");
						printf("\n");
						printf("From                 To                   Route      Miles\n");
						printf("-------------------- -------------------- ---------- -----\n");
						
						for (std::vector<Road *>::iterator begin_it = path->roads.begin(), it = begin_it, end_it = path->roads.end(); it != end_it; it++)
						{
							city1 = city2;
							city2 = this->cities[city1 == this->cities[(*it)->city1] ? (*it)->city2 : (*it)->city1];
							printf("%-20s %-20s %-10s %5u\n", city1.c_str(), city2.c_str(), (*it)->name.c_str(), (*it)->length);
						}
						
						printf("                                                     -----\n");
						printf("                                          Total      %5u\n", path->length);
						
						return;
				}
		}
};

int main(int argc, char *argv[]) {
	Map map;
	
	char line[1024];
	std::string city1, city2, road;
	
	while (true)
	{
		fgets(line, sizeof(line) / sizeof(char), stdin);
		if (line[0] == '\n')
			break;
		
		int part = 0;
		for (char *i = line, *start = line; *i != '\0'; i++)
			if (*i == ',')
			{
				switch (part) {
					case 0: // after city1
						city1 = std::string(start, i - start);
						break;
					
					case 1: // after city2
						city2 = std::string(start, i - start);
						break;
					
					case 2: // after road
						road = std::string(start, i - start);
						uint ct1, ct2;
						
						if (0 == map.citiesR.count(city1))
						{
							map.cities.push_back(city1);
							map.citiesR[city1] = ct1 = map.cities.size() - 1;
						}
						else
							ct1 = map.citiesR[city1];
						
						if (0 == map.citiesR.count(city2))
						{
							map.cities.push_back(city2);
							map.citiesR[city2] = ct2 = map.cities.size() - 1;
						}
						else
							ct2 = map.citiesR[city2];
						
						uint length;
						sscanf(i + 1, "%u", &length);
						
						Road *rd = new Road(road, length, ct1, ct2);
						
						if (NULL == map.roads[ct1][ct2] || map.roads[ct1][ct2]->length > rd->length)
							map.roads[ct1][ct2] = map.roads[ct2][ct1] = rd;
						break;
				}
				start = i + 1;
				part++;
			}
	}
	
	while (true)
	{
		if (feof(stdin))
			break;
		
		if (NULL == fgets(line, sizeof(line) / sizeof(char), stdin))
			break;
		
		map.solve(line);
	}
	
	return 0;
}
