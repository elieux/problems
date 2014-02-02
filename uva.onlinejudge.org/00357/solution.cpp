#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LINE_LENGTH 16

int main(int argc, char *argv[]) {
	unsigned long long int memo[30001];
	unsigned int money = 0, baux, aaux;
	register int i, j, k;
	long long unsigned int result;
	char line[LINE_LENGTH];
	
	memset(memo, 0, 30001 * sizeof(unsigned long long int));
	while (true)
	{
		if (NULL == fgets(line, LINE_LENGTH, stdin) || '\n' == line[0])
			break;
		sscanf(line, "%u", &money);
		
		result = 0;
		aaux = money % 50;
		for ( i = ( money / 50 ) ; i >= 0; i-- )
		{
			baux = aaux % 25;
			for ( j = ( aaux / 25 ) ; j >= 0; j--)
			{
				if (memo[baux] != 0)
					result += memo[baux];
				else
				{
					for ( k = ( baux / 10 ); k >= 0; k-- )
					{
						result += (baux - k * 10) / 5 + 1;
						memo[baux] += (baux - k * 10) / 5 + 1;
					}
				}
				baux += 25;
			}
			aaux += 50;
		}
		printf("There %s %llu way%s to produce %u cents change.\n", 1 == result ? "is only" : "are", result, 1 == result ? "" : "s", money);
	}
	
	return 0;
}
