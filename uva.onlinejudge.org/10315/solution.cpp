#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cstring>

#define CARDS_IN_HAND 5u

typedef struct {
	int rank;
	int suit;
} card;

typedef card hand[CARDS_IN_HAND];

typedef unsigned int uint;

typedef uint valuation(hand);

uint score_of(hand a_hand) {
	uint result = 0;
	
	for (uint i = 0; i < CARDS_IN_HAND; i++)
	{
		result *= 14;
		result += a_hand[i].rank;
	}
	
	return result;
}

int suit_of(char c) {
	return (int)c;
}

int rank_of(char c) {
	static int map[UCHAR_MAX];
	static bool initialized = false;
	
	if (!initialized)
	{
		memset(map, 0x00, sizeof(map));
		
		char ranks[] = "23456789TJQKA";
		for (uint i = 0; i < sizeof(ranks) - 1; i++)
			map[(int)ranks[i]] = i + 1;
	}
	
	return map[(int)c];
}

bool load_hand(hand a_hand) {
	uint i = 0;
	
	while (i < CARDS_IN_HAND)
	{
		if (feof(stdin))
			return false;
		
		char c = getc(stdin);
		if (!isalnum(c))
			continue;
		
		if (!a_hand[i].rank)
			a_hand[i].rank = rank_of(c);
		else // if (!a_hand[i].suit)
		{
			a_hand[i].suit = suit_of(c);
			i++;
		}
	}
	
	return true;
}

int compare_cards_reverse(const void *a, const void *b) {
	return ((const card *)b)->rank - ((const card *)a)->rank;
}

uint valuate_four_of_a_kind(hand a_hand) {
	if (a_hand[0].rank == a_hand[1].rank && a_hand[1].rank == a_hand[2].rank && a_hand[2].rank == a_hand[3].rank)
		return score_of((hand){ a_hand[0], a_hand[1], a_hand[2], a_hand[3], { 0, 0 } });
	if (a_hand[1].rank == a_hand[2].rank && a_hand[2].rank == a_hand[3].rank && a_hand[3].rank == a_hand[4].rank)
		return score_of((hand){ a_hand[1], a_hand[2], a_hand[3], a_hand[4], { 0, 0 } });
	
	return 0;
}

uint valuate_full_house(hand a_hand) {
	if (a_hand[0].rank == a_hand[1].rank && a_hand[1].rank == a_hand[2].rank && a_hand[3].rank == a_hand[4].rank)
		return score_of((hand){ a_hand[0], a_hand[1], a_hand[2], { 0, 0 }, { 0, 0 } });
	if (a_hand[0].rank == a_hand[1].rank && a_hand[2].rank == a_hand[3].rank && a_hand[3].rank == a_hand[4].rank)
		return score_of((hand){ a_hand[2], a_hand[3], a_hand[4], { 0, 0 }, { 0, 0 } });
	
	return 0;
}

uint valuate_flush(hand a_hand) {
	for (uint i = 1; i < CARDS_IN_HAND; i++)
		if (a_hand[i - 1].suit != a_hand[i].suit)
			return 0;
	
	return score_of(a_hand);
}

uint valuate_straight(hand a_hand) {
	for (uint i = 1; i < CARDS_IN_HAND; i++)
		if (a_hand[i - 1].rank != a_hand[i].rank + 1)
			return 0;
	
	return score_of(a_hand);
}

uint valuate_three_of_a_kind(hand a_hand) {
	if (a_hand[0].rank == a_hand[1].rank && a_hand[1].rank == a_hand[2].rank)
		return score_of((hand){ a_hand[0], a_hand[1], a_hand[2], { 0, 0 }, { 0, 0 } });
	if (a_hand[1].rank == a_hand[2].rank && a_hand[2].rank == a_hand[3].rank)
		return score_of((hand){ a_hand[1], a_hand[2], a_hand[3], { 0, 0 }, { 0, 0 } });
	if (a_hand[2].rank == a_hand[3].rank && a_hand[3].rank == a_hand[4].rank)
		return score_of((hand){ a_hand[2], a_hand[3], a_hand[4], { 0, 0 }, { 0, 0 } });
		
	return 0;
}

uint valuate_two_pairs(hand a_hand) {
	if (a_hand[0].rank == a_hand[1].rank && a_hand[2].rank == a_hand[3].rank)
		return score_of((hand){ a_hand[0], a_hand[1], a_hand[2], a_hand[3], a_hand[4] });
	if (a_hand[0].rank == a_hand[1].rank && a_hand[3].rank == a_hand[4].rank)
		return score_of((hand){ a_hand[0], a_hand[1], a_hand[3], a_hand[4], a_hand[2] });
	if (a_hand[1].rank == a_hand[2].rank && a_hand[3].rank == a_hand[4].rank)
		return score_of((hand){ a_hand[1], a_hand[2], a_hand[3], a_hand[4], a_hand[0] });
	
	return 0;
}

uint valuate_pair(hand a_hand) {
	if (a_hand[0].rank == a_hand[1].rank)
		return score_of((hand){ a_hand[0], a_hand[1], a_hand[2], a_hand[3], a_hand[4] });
	if (a_hand[1].rank == a_hand[2].rank)
		return score_of((hand){ a_hand[1], a_hand[2], a_hand[0], a_hand[3], a_hand[4] });
	if (a_hand[2].rank == a_hand[3].rank)
		return score_of((hand){ a_hand[2], a_hand[3], a_hand[0], a_hand[1], a_hand[4] });
	if (a_hand[3].rank == a_hand[4].rank)
		return score_of((hand){ a_hand[3], a_hand[4], a_hand[0], a_hand[1], a_hand[2] });
	
	return 0;
}

uint valuate_nothing(hand a_hand) {
	return score_of(a_hand);
}

uint valuate_straight_flush(hand a_hand) {
	if (valuate_flush(a_hand))
		return valuate_straight(a_hand);
	
	return 0;
}

bool do_one() {
	static valuation *valuations[] = {
		&valuate_straight_flush,
		&valuate_four_of_a_kind,
		&valuate_full_house,
		&valuate_flush,
		&valuate_straight,
		&valuate_three_of_a_kind,
		&valuate_two_pairs,
		&valuate_pair,
		&valuate_nothing
	};
	
	hand black = { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } };
	hand white = { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } };
	bool end;
	
	memset(black, 0x00, sizeof(black));
	end = !load_hand(black);
	if (end)
		return false;
	
	memset(white, 0x00, sizeof(white));
	end = !load_hand(white);
	if (end)
		return false;
	
	// printf("black: %d%c, %d%c, %d%c, %d%c, %d%c\n", black[0].rank, black[0].suit, black[1].rank, black[1].suit, black[2].rank, black[2].suit, black[3].rank, black[3].suit, black[4].rank, black[4].suit);
	// printf("white: %d%c, %d%c, %d%c, %d%c, %d%c\n", white[0].rank, white[0].suit, white[1].rank, white[1].suit, white[2].rank, white[2].suit, white[3].rank, white[3].suit, white[4].rank, white[4].suit);
	
	qsort(black, CARDS_IN_HAND, sizeof(card), compare_cards_reverse);
	qsort(white, CARDS_IN_HAND, sizeof(card), compare_cards_reverse);
	
	for (uint i = 0; i < sizeof(valuations); i++)
	{
		uint value_of_black = valuations[i](black);
		uint value_of_white = valuations[i](white);
		
		if (value_of_black || value_of_white)
		{
			if (value_of_black > value_of_white)
				printf("Black wins.\n");
			else if (value_of_black < value_of_white)
				printf("White wins.\n");
			else // if (value_of_black == value_of_white)
				printf("Tie.\n");
			
			return true;
		}
	}
	
	return true;
}

int main(int argc, char *argv[]) {
	argc = argc;
	argv = argv;
	
	bool end;
	
	do
	{
		end = !do_one();
	}
	while (!end);
	
	return 0;
}
