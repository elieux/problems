#include <stdio.h>
#include <string.h>

#define BUF_LEN 32

#define convert_endian(x) ((((x) & 0x000000FF) << 24) | (((x) & 0x0000FF00) << 8) | (((x) & 0x00FF0000) >> 8) | (((x) & 0xFF000000) >> 24))

int main(int argc, char *argv[]) {
	int input;
	char line[BUF_LEN];
	
	while (NULL != fgets(line, BUF_LEN, stdin) && 0 < strlen(line))
	{
		sscanf(line, "%d", &input);
		printf("%d converts to %d\n", input, convert_endian(input));
	}
	
	return 0;
}
