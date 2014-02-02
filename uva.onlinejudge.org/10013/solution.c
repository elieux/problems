#include <stdio.h>
#include <string.h>

#define BUF_LEN 8
#define CYCBUF_LEN 1000000

#define Atoi(x) ((x) - '0')
#define itoA(x) ((char)((x) + '0'))

int main(int argc, char *argv[]) {
	unsigned int cases, length;
	char line[BUF_LEN];
	char buffer[CYCBUF_LEN];
	unsigned int i, j, k;
	unsigned int a, b;
	
	fgets(line, BUF_LEN, stdin);
	sscanf(line, "%u", &cases);
	
	for (i = 0; i < cases; i++)
	{
		fgets(line, BUF_LEN, stdin);
		fgets(line, BUF_LEN, stdin);
		sscanf(line, "%u", &length);
		
		if (0 < i)
			putchar('\n');
		
		memset(buffer, 0, CYCBUF_LEN * sizeof(char));
		
		for (j = 0; j < length; j++)
		{
			if (CYCBUF_LEN <= j)
			{
				if (9 < buffer[j % CYCBUF_LEN])
					buffer[(j - 1) % CYCBUF_LEN] += buffer[j % CYCBUF_LEN] / 10;
				putchar(itoA(buffer[j % CYCBUF_LEN] % 10));
			}
			fgets(line, BUF_LEN, stdin);
			sscanf(line, "%u %u", &a, &b);
			buffer[j % CYCBUF_LEN] = a + b;
			k = j;
			while (9 < buffer[k % CYCBUF_LEN])
			{
				buffer[(k - 1) % CYCBUF_LEN] += buffer[k % CYCBUF_LEN] / 10;
				buffer[k % CYCBUF_LEN] %= 10;
				k--;
			}
		}
		if (j < CYCBUF_LEN)
			j += CYCBUF_LEN - length;
		for (; j < (length + CYCBUF_LEN); j++)
			putchar(itoA(buffer[j % CYCBUF_LEN] % 10));
		putchar('\n');
		fflush(stdout);
	}
	return 0;
}
