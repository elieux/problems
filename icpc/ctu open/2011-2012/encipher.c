#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LINE_LENGTH 10002


void doit(int ciph, char line[LINE_LENGTH]) {
	char *result;
	
	unsigned int p, pn, ps, pr;
	p = 0;
	pn = 0;
	while (line[p] != '\0' && line[p] != '\n')
	{
		if (line[p] != ' ')
			line[pn++] = toupper(line[p]);
		p++;
	}
	line[pn] = '\0';
	
	result = (char *)malloc(pn + 1);
	
	ps = 0;
	pr = 0;
	for (p = 0; p < pn; p++)
	{
		result[ps] = line[p];
		ps += ciph;
		if (ps >= pn)
			ps = ++pr;
	}
	result[p] = '\0';
	
	printf("%s\n", result);
}

int main(int argc, char *argv[]) {
	char line[LINE_LENGTH];
	int ciph;
	
	argc = argc;
	argv = argv;
	
	while (true)
	{
		fgets(line, LINE_LENGTH, stdin);
		sscanf(line, "%d\n", &ciph);
		if (ciph == 0)
			break;
		fgets(line, LINE_LENGTH, stdin);
		doit(ciph, line);		
	}
	
	return 0;
}
