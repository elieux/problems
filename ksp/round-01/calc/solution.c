#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;

int compute(int a, char op, int b) {
	switch (op) {
		case '+':
			return a + b;
		case '-':
			return a - b;
		case '*':
			return a * b;
		default:
			exit(1);
	}
}

int main() {
	uint iCase, nCases;
	scanf("%u", &nCases);
	
	for (iCase = 0; iCase < nCases; ++iCase)
	{
		int a, b;
		char op;
		
		scanf("%d %c %d", &a, &op, &b);
		printf("%d\n", compute(a, op, b));
	}
	
	return 0;
}
