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

typedef struct
{
	int v;
	int weight;
} edge;

typedef struct
{
	vector< edge > edges;
	int *degree;
	int vertices;
} graph;

int main(int argc, char *argv[]) 
{
	uint n = 0,m = 0;
	while ( cin >> n >> m ) 
	{
		edge* edges = new edge[n];
		vector< int > graph;
		for ( register uint i = 0; i < m; i++ )
		{
			uint temp_a, temp_b, temp_c;
			scanf("%u %u %u", &temp_a, &temp_b, &temp_c );
			edges[temp_a]
		}
		
		
	}
	
	return 0;
}
