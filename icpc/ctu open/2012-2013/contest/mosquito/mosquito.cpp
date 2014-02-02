#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <cmath>
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

int main(int argc, char *argv[]) 
{
	uint m = 0,p = 0,l = 0,e = 0,r = 0,s = 0,n = 0;
	
	while (cin >> m >> p >> l >> e >> r >> s >> n) 
	{
		//cout << "Debug" << m << " " << p << " " << l << " " << e << " " << r << " " << s << " " << n << endl;
		
		for ( register uint i = 0; i < n; i++ )
		{
			uint temp = m;
			if ( p != 0)
				m = ( p / s );
			else m = 0;
			
			if ( l != 0 )
				p = ( l / r );
			else p = 0;
				
			l = e * temp;
		}
		
		cout << m << endl;
	}
	
	return 0;
}
