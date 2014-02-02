#include <vector>
#include <queue>
#include <algorithm>
#include <cstdio>
#include <cstring>

#define MAXV 51

typedef struct
{
	std::vector<int> e[MAXV];
	int nv;
	int v_to_c[MAXV];
	int c_to_v[MAXV];
} graph;

void insert_edge(graph* g, int x, int y)
{
	g->e[x].push_back(y);
	g->e[y].push_back(x);
}

void go(graph *g, int v, std::vector<int>& a, int apos)
{
	while (!g->e[v].empty())
	{
		int v2 = g->e[v][0];
		g->e[v].erase(g->e[v].begin());
		g->e[v2].erase(find(g->e[v2].begin(), g->e[v2].end(), v));
		a.insert(a.begin() + apos, v);
		go(g, v2, a, apos + 1);
	}
}

std::vector<int> find_necklace(graph* g)
{
	// /**/ printf("scanning graph for odd edge count\n");
	std::vector<int> ans;
	for(int i = 0; i < g->nv; i++)
	{
		if((g->e[i].size())%2 == 1)
			return ans;
	}
	
	// /**/ printf("scanning graph for disconnections\n");
	int usable[MAXV];
	memset(usable, 1, sizeof(usable));
	std::queue<int> bfs;
	bfs.push(0);
	usable[0] = 0;
	while (!bfs.empty())
	{
		int v = bfs.front();
		bfs.pop();
		for (unsigned int e = 0; e < g->e[v].size(); e++)
			if (usable[g->e[v][e]])
			{
				usable[g->e[v][e]] = 0;
				bfs.push(g->e[v][e]);
			}
	}
	for (int i = 0; i < g->nv; i++)
		if (usable[i])
			return ans;
	
	// /**/ printf("looking for the cycle\n");
	memset(usable, 0, sizeof(usable));
	go(g, 0, ans, 0);
	
	return ans;
}

int main()
{
	int c;
	scanf("%d", &c);
	for(int a = 0; a < c; a++)
	{
		graph g;
		memset(g.v_to_c, -1, sizeof(g.v_to_c));
		memset(g.c_to_v, -1, sizeof(g.c_to_v));
		int beads;
		scanf("%d", &beads);
		int v = 0;
		while(beads--)
		{
			int c1, c2, v1, v2;
			scanf("%d %d", &c1, &c2);
			
			v1 = g.c_to_v[c1];
			if (v1 == -1)
			{
				v1 = v++;
				g.c_to_v[c1] = v1;
				g.v_to_c[v1] = c1;
			}
			v2 = g.c_to_v[c2];
			if (v2 == -1)
			{
				v2 = v++;
				g.c_to_v[c2] = v2;
				g.v_to_c[v2] = c2;
			}
			
			insert_edge(&g, v1, v2);
		}
		g.nv = v;
		
		std::vector<int> necklace = find_necklace(&g);
		// for(unsigned int i = 0; i < necklace.size() ; i++)
			// printf("%d-", necklace[i]);
		// printf(" : ");
		
		printf("Case #%d\n", a+1);
		if(necklace.size() == 0)
			printf("some beads may be lost\n");
		else
			for(unsigned int i = 0; i < necklace.size() ; i++)
			{
				int v1 = necklace[i];
				int v2 = necklace[(i+1)%necklace.size()];
				printf("%d %d\n", g.v_to_c[v1], g.v_to_c[v2]);
			}
		if(a != c - 1)
			printf("\n");
	}
}