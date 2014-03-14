#include <cstdio>
#include <cstdlib>
#include <cstring>

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

typedef unsigned int uint;

int main(int argc, char *argv[]) {
	uint r, c;
	uint x1, y1;
	uint x2, y2;
	
	while (true) {
		if (6 != scanf("%u %u %u %u %u %u", &r, &c, &x1, &y1, &x2, &y2))
			break;
		
		uint dx = x1 > x2 ? x1 - x2 : x2 - x1;
		uint dy = y1 > y2 ? y1 - y2 : y2 - y1;
		
		uint diag = min(dx, dy);
		uint lin = max(dx, dy) - diag;
		
		printf("%u\n", diag + lin);
	}
	
	return 0;
}
