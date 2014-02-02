#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

static unsigned int pole[14] = {
	0,
	2,
	7,
	5,
	30,
	169,
	441,
	1872,
	7632,
	1740,
	93313,
	459901,
	1358657,
	2504881
};

int main(int argc, char *argv[]) {
	char buffer[32];
	int cislo;
	
	do {
		fgets(buffer, 32, stdin);
		sscanf(buffer, "%d", &cislo);
		
		if (cislo == 0)
			break;
		
		printf("%d\n", pole[cislo]);
	} while (true);
	
	return 0;
}
