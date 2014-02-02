#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <queue>

using namespace std;


int main(int argc, char *argv[]) {
	
	argc = argc;
	argv = argv;
	
	int X = 0, Y = 0, N = 0;
	float r = 0.0f;
	
	while (true)
	{
		scanf("%d %d %d %f", &X, &Y, &N, &r);
		if (X == 0 && Y == 0 &&  N== 0 && r == 0.0f)
			break;
		
		bool valid = false;
		int n = N * 12;
		float x = (float)X;
		float y = (float)Y;
		r /= 100.0;
		r /= 12.0f;
		float fAux = ( x / y );
		if ( r==0.0f && fAux <= (float)n)
			valid = true;
		else if ( fAux < (float)n )
			for ( int  i = 0; i < n; i++ )
			{
				x = x + ( x * r ) - y;
				
				if ( x <= 0.0 )
				{
					valid = true;
					break;
				}
			}
	
		printf( valid ? "YES\n" : "NO\n" );
	}
	
	return 0;
}
