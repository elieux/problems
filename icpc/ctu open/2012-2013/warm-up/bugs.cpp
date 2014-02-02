#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

typedef unsigned int uint;

using namespace std;

int main(int argc, char *argv[]) 
{
	char line[1096];
	int lines = 0;
	
	
	while (true)
	{
		fgets(line, sizeof(line), stdin);
		if (feof(stdin))
			break;
		
		char mark[500];
		if (2 != sscanf(line, "%d %s", &lines, mark))
			break;
		
		int marklen = strlen(mark);
		
		for ( register int i = 0; i < lines; i++ )
		{
			int state = 0;
			fgets(line, sizeof(line), stdin);
			char *p;
			for (p = line; *p != '\0'; p++)
			{
				if (*p == mark[state])
					state++;
				else
				{
					for (; state > 0; state--)
						putchar(*(p - state));
					putchar(*p);
				}
				if (state == marklen)
					state = 0;
			}	
			for (; state > 0; state--)
				putchar(*(p - state));
			putchar(*p);
		}
	}
	
	
	
	
	return 0;
}
