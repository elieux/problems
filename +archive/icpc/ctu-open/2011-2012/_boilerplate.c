#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LINE_LENGTH 1024

void tle() {
	while (1);
}

void doit() {
}

int main(int argc, char *argv[]) {
	char line[LINE_LENGTH];
	
	argc = argc;
	argv = argv;
	
	while (true)
	{
		fgets(line, LINE_LENGTH, stdin);
		//~ sscanf(line, "");
		doit();
		
		//~ if ()
			//~ break;
	}
	
	return 0;
}
