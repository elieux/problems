#include <iostream>
#include <cstdlib>
#include <vector>
#include <stdio.h>
#include<algorithm>


using namespace std;

int main()
{
	
	int N;
	vector<int> member1;
	vector<int> member2;
	vector<int> member3;
	
	while (1) {
		scanf("%d", &N);
		if (N == 0) break;
		
		long long counter = 0;
		
		int t;
		
		for(int i  = 0 ; i < N; i++) {
			scanf("%d", &t);
			member1.push_back(t);
		}
		
		for(int i  = 0 ; i < N; i++) {
			scanf("%d", &t);
			member2.push_back(t);
		}
		
		for(int i  = 0 ; i < N; i++) {
			scanf("%d", &t);
			member3.push_back(t);
		}
		
		for(int i = 0; i < N; i++) {
			int t1; int t2;
			
			for(int j = i + 1; j < N; j++) {
				
				t1 = member1[i]; 
				t2 = member1[j];
				
				vector<int>::iterator it1;
				vector<int>::iterator it2;
				
				it1 = find(member2.begin(), member2.end(), t1);
				it2 = find(member2.begin(), member2.end(), t2);
				
				if(it1 > it2) continue;
				
				it1 = find(member3.begin(), member3.end(), t1);
				it2 = find(member3.begin(), member3.end(), t2);
				
				if(it1 > it2) continue;
				
				counter++;
			}
		}
		printf("%lld\n", counter);
		member1.clear();
		member2.clear();
		member3.clear();
	}
	return 0;
}
