#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>

#define min(a, b) (a) < (b) ? (a) : (b)
#define max(a, b) (a) > (b) ? (a) : (b)

typedef unsigned int uint;

int main(int argc, char *argv[]) {
	uint length, ants;
	
	while (true) {
		if (2 != scanf("%u %u", &length, &ants))
			break;
		
		uint leftmost = UINT_MAX, rightmost = 0;
		bool hasleftmost = false, hasrightmost = false;
		
		for (uint i = 0; i < ants; i++) {
			uint pos;
			char dir;
			scanf("%u %c", &pos, &dir);
			if (dir == 'R' && pos <= leftmost)
			{
				leftmost = pos;
				hasleftmost = true;
			}
			if (dir == 'L' && rightmost <= pos)
			{
				rightmost = pos;
				hasrightmost = true;
			}
		}
		
		uint toright = length - leftmost;
		uint toleft = rightmost;
		
		uint result;
		if (hasleftmost && hasrightmost)
			result = max(toleft, toright);
		else if (hasleftmost)
			result = toright;
		else if (hasrightmost)
			result = toleft;
		else
			printf("chyba\n");
		
		printf("The last ant will fall down in %u seconds.\n", result);
	}
	
	return 0;
}
