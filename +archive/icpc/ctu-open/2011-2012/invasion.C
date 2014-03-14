#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <queue>

using namespace std;

class node{
	public:
		vector<int> roadto;
		vector<int> roadtolen;
		unsigned int distance;
		bool danger;
		
		node(): distance(0xFFFFFFFFu), danger(false) {
		}
};

int infested = 0;
node* nod;

void go( int c, int n, unsigned int k )
{
	queue<int> q;
	q.push(c);
	
	nod[c].distance = 0;
	while (!q.empty())
	{
		c = q.front();
		q.pop();
		
		if (nod[c].distance < k && !nod[c].danger)
		{
			infested++;
			nod[c].danger = true;
		}
		
		for ( unsigned int i = 0; i < nod[c].roadto.size(); i++ )
		{
			if (nod[nod[c].roadto[i]].distance > (nod[c].distance + nod[c].roadtolen[i]))
			{
				nod[nod[c].roadto[i]].distance = nod[c].distance + nod[c].roadtolen[i];
				q.push(nod[c].roadto[i]);
			}
		}
	}
	printf("%d\n", n - infested);
}

int main(int argc, char *argv[]) {
	
	argc = argc;
	argv = argv;
	
	int n = 0; //cities
	int m = 0; // roads
	int a = 0; // aliens
	unsigned int k = 0; // distance

	
	queue<int> fro;
	
	while (true)
	{
		scanf("%d %d %d %u", &n, &m, &a, &k);
		if (n == 0 && m == 0 && a == 0 && k == 0)
			break;
		
		nod = new node[n + 1];
		infested = 0;
		for ( register int i = 0; i < m; i++ )
		{
			int e,f,g;
			scanf("%d %d %d", &e, &f, &g );
			nod[e].roadto.push_back( f );
			nod[f].roadto.push_back( e );
			nod[e].roadtolen.push_back( g );
			nod[f].roadtolen.push_back( g );
		}
		
		for( int i = 0; i < a; i++ )
		{
			int e;
			scanf( "%d" , &e );
			fro.push( e );
		}
		
		while ( !fro.empty() )
		{
			int act = fro.front();
			fro.pop();
			go(act, n, k);
		}
		printf("\n");
	}
	
	return 0;
}
