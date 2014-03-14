#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LINE_LENGTH 102400

void tle() {
	while (1);
}

void doit(char line[LINE_LENGTH]) {
	unsigned int p;
	unsigned int num, min, max, prod, add;
	
	p = 0;
	min = -1;
	max = 0;
	prod = -1;
	add = -1;
	num = 0;
	while (line[p] != '\n' && line[p] != '\0')
	{
		if (isdigit(line[p]))
		{
			num *= 10;
			num += line[p] - '0';
		}
		else
		{
			if (line[p] == '+')
			{
				if (prod == -1u)
					prod = 1;
				prod *= num;
				min += prod;
				prod = -1u;
				
				add += num;
			}
			else if (line[p] == '*')
			{
				if (add == -1u)
					add = 0;
				add += num;
				max *= add;
				add = -1u;
				
				prod *= num;
			}
			num = 0;
		}
		p++;
	}
	
	printf("%u %u\n", min, max);
}

int main(int argc, char *argv[]) {
	char line[LINE_LENGTH];
	
	argc = argc;
	argv = argv;
	
	while (true)
	{
		fgets(line, LINE_LENGTH, stdin);
		if (strcmp(line, "0\n") == 0)
			break;
		doit(line);
		
	}
	
	return 0;
}
