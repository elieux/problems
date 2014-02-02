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

typedef struct
{
	int x, y;
} point;

#define EPS (1e-7L)
#define PI (4.0L * atanl(1.0L))
#define MAX 101

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define abs(a) ((a) < 0 ? -(a) : (a))

vector<point> directions;
int r, c;

bool inrange(point test)
{
	return test.x >= 1 && test.x <= r && test.y >= 1 && test.y <= c;
}

int solve(int grid[MAX][MAX], point g, point l)
{
	queue<point> q;
	q.push(g);
	
	while(!q.empty())
	{
		point aux = q.front();
		q.pop();
		
		if (aux.x == l.x && aux.y == l.y)
			return grid[aux.x][aux.y];
		
		for (uint i = 0; i < directions.size(); i++)
		{
			point temp = aux;
			temp.x += directions[i].x;
			temp.y += directions[i].y;
			if (inrange(temp))
				if (grid[temp.x][temp.y] > grid[aux.x][aux.y] + 1)
				{
					grid[temp.x][temp.y] = grid[aux.x][aux.y] + 1;
					q.push(temp);
				}
		}
	}
	
	return -1;
}
			

int main(int argc, char *argv[]) {
	
	directions.push_back((point){  2, -1});
	directions.push_back((point){  2,  1});
	directions.push_back((point){  1,  2});
	directions.push_back((point){  1, -2});
	directions.push_back((point){ -1, -2});
	directions.push_back((point){ -1,  2});
	directions.push_back((point){ -2, -1});
	directions.push_back((point){ -2,  1});
	
	
	point grass, leaf;
	
	while (true) {
		if (scanf("%d %d %d %d %d %d", &r, &c, &grass.x, &grass.y, &leaf.x, &leaf.y) != 6)
			break;
		int grid[MAX][MAX];
		for (int i = 1; i <= r; i++)
			for (int j = 1; j <= c; j++)
				grid[i][j] = INT_MAX;
		grid[grass.x][grass.y] = 0;
			
		int shortestpath = solve(grid, grass, leaf);
		if (shortestpath == -1)
			printf("impossible\n");
		else
			printf("%d\n", shortestpath);
		
		
	}
	
	return 0;
}
