#include <cstdlib>
#include <cstdio>
#include <cstring>

#define MAX_FIELD 8u
#define ATTACK 100lu
#define PRINT_NUMBER "%llu"

#define ij(i, j) (MAX_FIELD * (i) + (j))

typedef unsigned int uint;
typedef long long unsigned int NUMBER;
typedef uint Field[MAX_FIELD * MAX_FIELD];

void printp(int n, Field field) {
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%3u ", field[ij(i, j)]);
		printf("\n");
	}
	printf("\n");
}

void ways(uint k, int n, Field field, NUMBER &number) {
	if (k == 0)
	{
		*number++;
		return;
	}
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (field[ij(i, j)] <= k)
			{
				field[ij(i, j)] = k;
				
				if (k > 1)
					for (int a = 1; a < n; a++)
					{
						if (i+a < n && j+a < n)
							field[ij(i+a, j+a)] += ATTACK;
						if (i+a < n && j-a >= 0)
							field[ij(i+a, j-a)] += ATTACK;
						if (i-a >= 0 && j+a < n)
							field[ij(i-a, j+a)] += ATTACK;
						if (i-a >= 0 && j-a >= 0)
							field[ij(i-a, j-a)] += ATTACK;
					}
				
			// system("cls");
			// printp(n, field);
			// system("pause");
				ways(k-1, n, field, number);
				
				if (k > 1)
					for (int a = 1; a < n; a++)
					{
						if (i+a < n && j+a < n)
							field[ij(i+a, j+a)] -= ATTACK;
						if (i+a < n && j-a >= 0)  
							field[ij(i+a, j-a)] -= ATTACK;
						if (i-a >= 0 && j+a < n)  
							field[ij(i-a, j+a)] -= ATTACK;
						if (i-a >= 0 && j-a >= 0) 
							field[ij(i-a, j-a)] -= ATTACK;
					}
			}
}

int main(int argc, char *argv[]) {
	int n;
	uint k;
	Field field;
	
	(void)argc;
	(void)argv;
	
	while(true)
	{
		scanf("%d %u", &n, &k);
		if (n == 0 && k == 0)
			break;
		
		memset(field, 0x00, sizeof(field));
		NUMBER answer = 0;
		ways(k, n, field, answer);
		
		printf(PRINT_NUMBER "\n", answer);
	}
	
	return 0;
}
