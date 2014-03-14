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

//~ using namespace std;

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

int main(int argc, char *argv[]) {
	while (true) {
		int ants, len;
		
		if (2 != scanf("%u %u\n", &len, &ants))
			break;
		
		int maxL = 0, minR = len, mindist = len;
		bool existL = false, existR = false;
		std::vector<int> antssssss;
		char wood[len + 1];
		memset(wood, 0, len + 1);
		
		for (int ant = 0; ant < ants; ant++) {
			int start;
			char dir;
			
			scanf("%u %c", &start, &dir);
			
			if (dir == 'L') {
				existL = true;
				maxL = max(maxL, start);
			} else if (dir == 'R') {
				existR = true;
				minR = min(minR, start);
			}
			wood[start] = dir;
			
			int aux = len%2 ? min(abs(len/2 - start), abs(len/2 + 1 - start)) : abs((len >>1) - start);
			
			if (aux < mindist) 
			{
				antssssss.clear();
				antssssss.push_back(start);
				mindist = aux;
			}
			else
				if(aux == mindist)
					antssssss.push_back(start);
		}
		
		bool debug = true;
		if (debug) { for (int i = 0; i <= len; i++) putchar(wood[i] == '\0' ? '0' : wood[i]); putchar('\n'); }
		
		int L = maxL, R = len - minR;
		if (existL && existR) {
			if (minR < maxL) {
				int cl = len / 2, cr = len / 2 + (len % 2);
				if (debug) printf("cl: %d cr: %d\n", cl, cr);
				
				int dl = INT_MAX, dr = INT_MAX;
				bool hasl, hasr;
				bool hasR, hasL;
				
				bool haslL = false, haslR = false;
				int lL, lR, dlL, dlR;
				for (int l = cl; l >= 0; l--) {
					if (haslL && haslR)
						break;
					
					if (!haslL && wood[l] == 'L') {
						haslL = hasL = hasl = true;
						lL = l;
						dlL = len%2 ? min(abs(len/2 - l), abs(len/2 + 1 - l)) : abs((len >>1) - l);
						if (dlL < dl)
							dl = dlL;
					} else if (!haslR && wood[l] == 'R') {
						haslR = hasR = hasl = true;
						lR = l;
						dlR = len%2 ? min(abs(len/2 - l), abs(len/2 + 1 - l)) : abs((len >>1) - l);
						if (dlR < dl)
							dl = dlR;
					}
				}
				if (debug) printf("haslL: %d lL: %d dlL: %d\n", haslL, lL, dlL);
				if (debug) printf("haslR: %d lR: %d dlR: %d\n", haslR, lR, dlR);
				
				bool hasrL = false, hasrR = false;
				int rL, rR, drL, drR;
				for (int r = cr; r <= len; r++) {
					if (hasrL && hasrR)
						break;
					
					if (!hasrL && wood[r] == 'L') {
						hasrL = hasL = hasr = true;
						rL = r;
						drL = len%2 ? min(abs(len/2 - r), abs(len/2 + 1 - r)) : abs((len >>1) - r);
						if (drL < dr)
							dr = drL;
					} else if (!hasrR && wood[r] == 'R') {
						hasrR = hasR = hasr = true;
						rR = r;
						drR = len%2 ? min(abs(len/2 - r), abs(len/2 + 1 - r)) : abs((len >>1) - r);
						if (drR < dr)
							dr = drR;
					}
				}
				if (debug) printf("hasrL: %d rL: %d drL: %d\n", hasrL, rL, drL);
				if (debug) printf("hasrR: %d rR: %d drR: %d\n", hasrR, rR, drR);
				
				int result1, result2;
				
				if (hasl && hasr) {
					if (haslR && hasrL && (!haslL || lL < lR) && (!hasrR || rL < rR)) {
						if (dlR == drR) {
							result1 = lR;
							result2 = rL;
						} else if (dlR < drL) {
							result1 = lR;
							result2 = -1;
						} else if (drL < dlR) {
							result1 = rL;
							result2 = -1;
						}
					} else if (haslL && hasrR && (!haslR || lR < lL) && (!hasrL || rR < rL)) {
						if (dlL == drR && haslR && lR < lL && hasrL && rR < rL) {
							result1 = lL;
							result2 = rR;
						} else if (dlL < drR && haslR && lR < lL) {
							result1 = lL;
							result2 = -1;
						} else if (drR < dlL && hasrL && rR < rL) {
							result1 = rR;
							result2 = -1;
						}
					} else if (haslL && hasrL && (haslR && lR < lL) && (!hasrR || rL < rR)) {
					} else if (haslL && hasrL && (!haslR || lR < lL) && (hasrR && rL < rR)) {
					} else if (haslR && hasrR && (!haslL || lL < lR) && (!hasrL || rR < rL)) {
					}
				} else if (hasl) { // mame haslR, haslL // lR < lL
					result1 = lL;
					result2 = -1;
				} else if (hasr) { // mame hasrR, hasrL // rR < rL
					result1 = rR;
					result2 = -1;
				} else {
					printf("not gonna happen, ever!!!\n");
				}
				/* 
				if (haslR && hasrL && (!haslL || lL < lR) && (!hasrR || rL < rR)) {
					result1 = lR;
					result2 = rL;
					if (debug) printf("%d: (haslR && hasrL && (!haslL || lL < lR) && (!hasrR || rL < rR))\n", __LINE__);
				} else if (haslR && haslL && (lR < lL) && hasrR && hasrL && (rR < rL)) {
					//~ if (dlL < drR) {
						//~ result1 = lR;
						//~ result2 = lL;
					//~ } else if (dlL > drR) {
						//~ result1 = rL;
						//~ result2 = rR;
					//~ } else {
						result1 = lL;
						result2 = rR;
					//~ }
					if (debug) printf("%d: ((haslR && haslL && (lR < lL) && hasrR && hasrL && (rL < rR))\n", __LINE__);
				} else if (haslR && haslL && (lR < lL)) {
					result1 = lR; 
					result2 = lL;
					if (debug) printf("%d: (haslR && haslL && (lR < lL))\n", __LINE__);
				} else if (hasrR && hasrL && (rR < rL)) {
					result1 = rR;
					result2 = rL;
					if (debug) printf("%d: (hasrR && hasrL && (rL < rR))\n", __LINE__);
				} else if (haslR && haslL && (lR > lL)) {
					result1 = lL; 
					result2 = -1;
					if (debug) printf("%d: (haslR && haslL && (lR < lL))\n", __LINE__);
				} else if (hasrR && hasrL && (rR > rL)) {
					result1 = rR;
					result2 = -1;
					if (debug) printf("%d: (hasrR && hasrL && (rL < rR))\n", __LINE__);
				} else {
					// not gonna happen
					printf("Bleee\n\n");
				} */
				
				if (result2 == -1)
					printf("The last ant will fall down in %d seconds - started at %d.\n", max(L, R), result1);
				else
					printf("The last ant will fall down in %d seconds - started at %d and %d.\n", max(L, R), min(result1, result2), max(result1, result2));
			} else {
				if(antssssss.size() == 2)
					printf("The last ant will fall down in %d seconds - started at %d and %d.\n", max(L, R), antssssss[0], antssssss[1]);
				else
					printf("The last ant will fall down in %d seconds - started at %d.\n", max(L, R), antssssss[0]);
			}
		} else if (existR) {
			printf("The last ant will fall down in %d seconds - started at %d.\n", R, minR);
		} else if (existL) {
			printf("The last ant will fall down in %d seconds - started at %d.\n", L, maxL);
		} else {
			// not gonna happen
		}
	}
	
	return 0;
}
