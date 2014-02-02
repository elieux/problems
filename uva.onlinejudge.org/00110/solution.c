#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LEN 16

void getChars(char *result, char start, unsigned int n) {
	unsigned int i;
	
	for (i = 0; n > i; i++)
		result[i] = start + i;
	result[i] = '\0';
}

void printWithCommas(char *chars) {
	unsigned int i, length;
	
	length = strlen(chars);
	for (i = 0; length > i; i++)
	{
		if (0 < i)
			printf(",");
		printf("%c", chars[i]);
	}
}

void printindent(unsigned int n) {
	unsigned int i;
	
	for (i = 0; n > i; i++)
		printf(" ");
}

void printsort(unsigned int done, char* chars, unsigned int indent) {
	unsigned int length;
	unsigned int i, j;
	char t;
	char buffer[BUFFER_LEN];
	
	length = strlen(chars);
	
	if (done == length)
	{
		printindent(indent);
		printf("writeln(");
		printWithCommas(chars);
		printf(")\n");
		return;
	}
	
	for (i = 0; done >= i; i++)
	{
		printindent(indent);
		if (0 < i)
			printf("else ");
		if (done > i)
			printf("if %c < %c then", chars[done], chars[i]);
		printf("\n");
		for (j = 0; i > j; j++)
			buffer[j] = chars[j];
		buffer[j++] = chars[done];
		for (; done > (j - 1); j++)
			buffer[j] = chars[j - 1];
		for (; length > j; j++)
			buffer[j] = chars[j];
		buffer[j] = '\0';
		printsort(done + 1, buffer, indent + 2);
	} 
}

int main(int argc, char *argv[]) {
	unsigned int cases;
	unsigned int i, j;
	unsigned int n;
	char buffer[BUFFER_LEN];
	
	fgets(buffer, BUFFER_LEN, stdin);
	sscanf(buffer, "%u", &cases);
	
	for (i = 0; cases > i; i++)
	{
		if (0 < i)
			printf("\n");
		fgets(buffer, BUFFER_LEN, stdin);
		fgets(buffer, BUFFER_LEN, stdin);
		sscanf(buffer, "%u", &n);
		
		printf("\
program sort(input,output);\n\
var\n\
");
		getChars(buffer, 'a', n);
		printWithCommas(buffer);
		printf("\
 : integer;\n\
begin\n\
  readln(\
");
		printWithCommas(buffer);
		printf(");\n");
		printsort(1, buffer, 2);
		printf("end.\n");
	}
	
	return 0;
}
