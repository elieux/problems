#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <climits>

#include <iostream>
#include <algorithm>

#include <vector>
#include <string>
#include <map>
#include <queue>
#include <deque>
#include <stack>
#include <set>

using namespace std;

typedef unsigned int uint;
typedef long double num;
typedef long long int lint;
typedef struct { int x, y; } intpoint;
typedef struct { num x, y; } numpoint;
typedef struct { lint x, y; } lintpoint;

#define EPS (1e-7L)
#define PI (4.0L * atanl(1.0L))

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define abs(a) ((a) < 0 ? -(a) : (a))

#define BUG (1u << 10u)
#define BUFFER (2u << 20u)

int main(int argc, char *argv[]) {
	char bug[BUG];
	char *buffer = (char *)malloc(BUFFER * sizeof(char));
	
	while (true) {
		uint lines;
		
		if (2 != scanf("%u %s\n", &lines, bug))
			break;
		
		uint buglen = strlen(bug);
		uint start0 = UINT_MAX;
		uint s0 = 0;
		
		for (uint line = 0; line < lines; line++) {
			uint p, s = 0;
			
			fgets(buffer, BUFFER, stdin);
			for (p = 0; buffer[p] != '\0'; p++) {
				if (buffer[p] == bug[s] || buffer[p] == bug[0]) {
					if (buffer[p] != bug[s])
						s = 0;
					
					const uint start = p - s;
					
					if (start < start0)
					{
						start0 = start;
						s0 = s;
					}
					if (1 + s == buglen) {
						if (start0 == start) {
							s = 0;
							s0 = 0;
							start0 = UINT_MAX;
						} else {
							const uint len0 = start - start0;
							const uint start1 = p + 1 - len0; //?
							memcpy(buffer + start1, buffer + start0, len0);
							s = s0;
							start0 = start1;
						}
					} else {
						s++;
					}
				} else {
					for (uint q = p - s; q <= p; q++)
						putchar(buffer[q]);
					s = 0;
					s0 = 0;
					start0 = UINT_MAX;
				}
			}
			for (uint q = p - s; q < p; q++)
				putchar(buffer[q]);
		}
	}
	
	return 0;
}
