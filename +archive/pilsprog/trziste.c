#include <stdio.h>
#include <string.h>
#define MAX 1000
#define POCET 100
#ifdef DEBUG
#undef DEBUG
#endif

void parse(const char *str, int *m)
{
	int k, l;
	
	if (strchr(str, '*') != NULL)
	{
		sscanf(str, " %d * %d ", &k, &l);
#ifdef DEBUG
/**/printf("%d %d\n", k, l);
#endif
		*m += k * l;
	}
	else
	{
		sscanf(str, " %d ", &k);
#ifdef DEBUG
/**/printf("%d\n", k);
#endif
		*m += k;
	}
}

int main()
{
	char a[MAX], *b;
	int money;
	
	gets(a);
#ifdef DEBUG
/**/puts(a);
#endif
	
	money = 0;
	b = strtok(a, "+");
	parse(b, &money);
	while ((b = strtok(NULL, "+")) != NULL)
		parse(b, &money);
	
	printf("%d\n", money);
	
	return 0;
}
