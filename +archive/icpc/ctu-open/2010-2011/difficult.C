#include <iostream>
#include <cstdlib>
#include <vector>
#include <stdio.h>
#include<algorithm>
#include <map>


using namespace std;

#define MAX 150000

int main()
{
	char *line;
	int N = 0;
	int asdf;
	asdf = 0;
	while (1) {
		line = new char[2000000];
		if (asdf > 0)
			fgets(line, 2000000, stdin);
		asdf++;
		fgets(line, 2000000, stdin);
		sscanf(line, "%d", &N);
		if (N == 0) break;
		
		long long counter = 0;
		map<int,int> member1;
		map<int,int> member2;
		map<int,int> member3;
		
		int t;
		
		int p, q;
		p = 0;
		fgets(line, 2000000, stdin);
		for(int i  = 0 ; i < N; i++) {
			t = 0;
			while (line[p] == ' ') p++;
			while (line[p] != ' ')
			{
				t *= 10;
				t += line[p++] - '0';
			}
			member1[t - 1] = i;
		}
		p = 0;
		fgets(line, 2000000, stdin);
		for(int i  = 0 ; i < N; i++) {
			t = 0;
			while (line[p] == ' ') p++;
			while (line[p] != ' ')
			{
				t *= 10;
				t += line[p++] - '0';
			}
			member2[t - 1] = i;
		}
		p = 0;
		fgets(line, 2000000, stdin);
		for(int i  = 0 ; i < N; i++) {
			t = 0;
			while (line[p] == ' ') p++;
			while (line[p] != ' ')
			{
				t *= 10;
				t += line[p++] - '0';
			}
			member3[t - 1] = i;
		}
		
/*		for(int i  = 0 ; i < N; i++) {
			if (i > 0)
				getchar();
			member3[t - 1] = getchar() - '0';
		}
*/		
		//~ *((int*)(0)) = 23;
		
		for(int i = 0; i < N; i++) {
			//int t1; int t2;
			
			for(int j = i + 1; j < (i + 2); j++) {
				
				if(member1[i] < member1[j]) {
					
					if(member2[i] > member2[j] ) continue;
					if(member3[i] > member3[j] ) continue;
					counter++;
				} else {
					if(member2[i] < member2[j] ) continue;
					if(member3[i] < member3[j] ) continue;
					counter++;
				}
				
				
				/*
				t1 = member1[i]; 
				t2 = member1[j];
				
				int *it1;
				int *it2;
				
				it1 = find(member2, &(member2[N]), t1);
				it2 = find(member2, &(member2[N]), t2);
				
				if(it1 > it2) continue;
				
				it1 = find(member3, &(member3[N]), t1);
				it2 = find(member3, &(member3[N]), t2);
				
				if(it1 > it2) continue;
				
				counter++;
				*/
			}
		}
		printf("%lld\n", counter);
	}
	return 0;
}
