#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define LINE_LENGTH 256

unsigned int sum(unsigned int n) {
	unsigned int i;
	unsigned int result;
	
	result = 0;
	for (i = 1; i < 10000000; i *= 10)
		result += (n / i) % 10;
	return result;
}

int main(int argc, char *argv[]) {
	char line[LINE_LENGTH];
	unsigned int i, j, k;
	unsigned int n, nSum;
	
	argc = argc; argv = argv; i = i; j = j; k = k;
	
	while (true)
	{
		fgets(line, LINE_LENGTH, stdin);
		sscanf(line, "%u", &n);
		if (0 == n)
			break;
		nSum = sum(n);
		
		i = 11;
		while (sum(i * n) != nSum)
			i++;
		printf("%u\n", i);
	}
	
	return 0;
}