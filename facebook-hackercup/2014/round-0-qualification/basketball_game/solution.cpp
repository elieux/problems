#include <iostream>
#include <algorithm>
#include <exception>
#include <vector>
#include <functional>
#include <set>
#include <list>

typedef unsigned int uint;

struct Player {
	std::string name;
	uint percentage;
	uint height;
	uint minutes;
	
	Player():
		name(""),
		percentage(0),
		height(0),
		minutes(0) {
	}
};

typedef std::vector<Player> Players;
typedef std::reference_wrapper<Player> PlayerRef;
typedef std::list<PlayerRef> Field, Bench;

bool operator< (const Player& a, const Player& b) { // draft number ordering
	if (a.minutes != b.minutes)
		return a.minutes < b.minutes;
	if (a.percentage != b.percentage)
		return a.percentage > b.percentage;
	if (a.height != b.height)
		return a.height > b.height;
	throw std::exception();
}

void rotate(Field& field, Bench& bench) {
	if (bench.size() == 0)
		return;
	
	auto leave_player = std::max_element(field.begin(), field.end());
	PlayerRef leave_player_ref = *leave_player;
	field.erase(leave_player);
	
	auto enter_player = std::min_element(bench.begin(), bench.end());
	PlayerRef enter_player_ref = *enter_player;
	bench.erase(enter_player);
	
	field.push_back(enter_player_ref);
	bench.push_back(leave_player_ref);
}

int main() {
	uint nCases;
	std::cin >> nCases;
	
	for (uint iCase = 0; iCase < nCases; iCase++)
	{
		uint nPlayers, minute, playersOnField;
		std::cin >> nPlayers >> minute >> playersOnField;
		
		Players players;
		for (uint iPlayer = 0; iPlayer < nPlayers; iPlayer++)
		{
			Player player;
			std::cin >> player.name >> player.percentage >> player.height;
			players.push_back(player);
		}
		std::sort(players.begin(), players.end());
		
		Field field1, field2;
		for (uint iPlayer = 0; iPlayer < playersOnField * 2; iPlayer++)
		{
			Field& field = iPlayer % 2 == 0 ? field1 : field2;
			field.push_back(std::ref(players[iPlayer]));
		}
		
		Bench bench1, bench2;
		for (uint iPlayer = playersOnField * 2; iPlayer < nPlayers; iPlayer++)
		{
			Bench& bench = iPlayer % 2 == 0 ? bench1 : bench2;
			bench.push_back(std::ref(players[iPlayer]));
		}
		
		for (uint i = 0; i < minute; i++)
		{
			for (Player& player : field1)
				player.minutes++;
			for (Player& player : field2)
				player.minutes++;
			
			rotate(field1, bench1);
			rotate(field2, bench2);
		}
		
		std::multiset<std::string> playerNames;
		for (Player& player : field1)
			playerNames.insert(player.name);
		for (Player& player : field2)
			playerNames.insert(player.name);
		
		
		std::cout << "Case #" << (iCase + 1) << ": ";
		uint i = 0;
		for (std::string playerName : playerNames)
		{
			if (i > 0)
				std::cout << " ";
			std::cout << playerName;
			i++;
		}
		std::cout << std::endl;
	}
	
	return 0;
}
