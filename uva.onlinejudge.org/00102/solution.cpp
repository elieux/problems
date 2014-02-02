#include <cstdio>
#include <cstring>
#include <climits>

typedef unsigned int uint;

typedef uint Bin[3];

const char colors[] = "BGC";
uint numbers[256];

void solve(Bin bins[3], char result[4], uint &min, bool used[3], char current[4], uint container) {
	if (container == 3)
	{
		uint moved = 0;
		
		for (uint i = 0; i < 3; i++)
			for (uint color = 0; color < 3; color++)
				if (color != numbers[current[i]])
					moved += bins[i][color];
		
		if (moved <= min)
		{
			if (moved < min || strcmp(current, result) < 0)
				strcpy(result, current);
			min = moved;
		}
		
		return;
	}
	
	for (uint color = 0; color < 3; color++)
	{
		if (used[color])
			continue;
		
		current[container] = colors[color];
		used[color] = true;
		solve(bins, result, min, used, current, container + 1);
		used[color] = false;
		current[container] = ' ';
	}
}

void solve(Bin bins[3], char result[], uint &min) {
	bool used[] = { false, false, false };
	char current[] = "   ";
	solve(bins, result, min, used, current, 0);
}

int main(int argc, char *argv[]) {
	argc = argc;
	argv = argv;
	
	for (uint i = 0; i < sizeof(colors) / sizeof(char) - 1; i++)
		numbers[(uint)colors[i]] = i;
	
	char line[256];
	
	while (!feof(stdin))
	{
		Bin bins[3];
		
		if (NULL == fgets(line, sizeof(line) / sizeof(char), stdin))
			break;
		if (9 != sscanf(line, "%u %u %u %u %u %u %u %u %u", &bins[0][0], &bins[0][1], &bins[0][2], &bins[1][0], &bins[1][1], &bins[1][2], &bins[2][0], &bins[2][1], &bins[2][2]))
			break;
		
		char result[] = "XXX";
		uint min = UINT_MAX;
		
		solve(bins, result, min);
		
		printf("%s %u\n", result, min);
	}
	
	return 0;
}
