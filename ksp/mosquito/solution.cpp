#include <iostream>
#include <algorithm>

typedef unsigned int uint;

struct State {
	uint mosquitos, pupae, larvae;
	
	State(uint mosquitos, uint pupae, uint larvae):
		mosquitos(mosquitos),
		pupae(pupae),
		larvae(larvae) {
	}
	
	State():
		mosquitos(0),
		pupae(0),
		larvae(0) {
	}
};

int main() {
	while (true)
	{
		State state;
		std::cin >> state.mosquitos >> state.pupae >> state.larvae;
		
		uint mosquito_to_egg_multipler, larva_to_pupa_divisor, pupa_to_mosquito_divisor;
		std::cin >> mosquito_to_egg_multipler >> larva_to_pupa_divisor >> pupa_to_mosquito_divisor;
		
		uint nWeeks;
		std::cin >> nWeeks;
		
		if (std::cin.fail())
			break;
		
		for (uint iWeek = 0; iWeek < nWeeks; ++iWeek)
		{
			state = State(
				state.pupae / pupa_to_mosquito_divisor,
				state.larvae / larva_to_pupa_divisor,
				state.mosquitos * mosquito_to_egg_multipler );
		}
		
		std::cout << state.mosquitos << std::endl;
	}
	return 0;
}
