#include <algorithm>
#include <cstdio>
#include <cstring>

typedef unsigned int uint;

int main(int argc, char *argv[]) {
	char a[1024], b[1024], x[1024];
	
	(void)argc;
	(void)argv;
	
	while (true)
	{
		char *res;
		
		res = fgets(a, sizeof(a) * sizeof(char), stdin);
		if (res == NULL)
			break;
		
		res = fgets(b, sizeof(a) * sizeof(char), stdin);
		if (res == NULL)
			break;
		
		{
			const uint alen = strlen(a) - 1;
			const uint blen = strlen(b) - 1;
			
			a[alen] = '\0';
			b[blen] = '\0';
			
			std::sort(a, a + alen);
			std::sort(b, b + blen);
			
			{
				char *ap = a, *bp = b, *xp = x;
				const char *ae = ap + alen, *be = bp + blen;
				
				while (ap != ae && bp != be)
				{
					if (*ap == *bp)
					{
						*xp = *ap;
						xp++;
						ap++;
						bp++;
					}
					else if (*ap < *bp)
						ap++;
					else // if (*bp < *ap)
						bp++;
				}
				
				*xp = '\0';
			}
		}
		
		printf("%s\n", x);
	}
	
	return 0;
}
