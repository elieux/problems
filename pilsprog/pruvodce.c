#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define min(x, y) (((x) < (y)) ? (x) : (y))
#define true 1
#define false 0

int nachazi_se(short int *kde, short int co)
{
	int i;
	
	for (i = 2; i <= kde[0]; i++)
		if (kde[i] == co)
			return true;
	return false;
}

int main()
{
	int i, n, r, posledni;
	short int y, s, d, t;
	short int *a, *b, *c, *buf, *vysledek;
	short int **fronta;
	size_t siz;
	
	scanf("%d %d", &n, &r);
	siz = n * 2 * sizeof(short int);
	a = malloc(r * sizeof(short int));
	b = malloc(r * sizeof(short int));
	c = malloc(r * sizeof(short int));
	buf = malloc(siz);
	vysledek = malloc(siz);
	fronta = malloc(r * sizeof(int *));
	for (i = 0; i < r; i++)
		scanf("%hd %hd %hd", &a[i], &b[i], &c[i]);
	scanf("%hd %hd %hd", &s, &d, &t);
	scanf("%d", &i);
	
	vysledek[0] = 3;
	vysledek[1] = 0;
	vysledek[2] = s;
	vysledek[3] = d;
	fronta[0] = malloc(siz);
	fronta[0][0] = 2;
	fronta[0][1] = 16384;
	fronta[0][2] = s;
	posledni = 0;
	while (posledni >= 0)
	{
		memcpy(buf, fronta[posledni], siz);
		free(fronta[posledni--]);
		if (buf[buf[0]] == d)
		{
			if (buf[1] > vysledek[1])
				memcpy(vysledek, buf, siz);
		}
		else
			for (i = 0; i < r; i++)
			{
				if ((a[i] == buf[buf[0]]) || (b[i] == buf[buf[0]]))
				{
					if (a[i] == buf[buf[0]])
						y = b[i];
					if (b[i] == buf[buf[0]])
						y = a[i];
					if (!nachazi_se(buf, y))
					{
						fronta[++posledni] = malloc(siz);
						memcpy(fronta[posledni], buf, siz);
						fronta[posledni][++fronta[posledni][0]] = y;
						fronta[posledni][1] = min(fronta[posledni][1], c[i]);
					}
				}
		}
	}
	
	printf("%d\n", (int) ceil(((float) t) / (vysledek[1] - 1)));
	
	free(a);
	free(b);
	free(c);
	free(buf);
	free(vysledek);
	free(fronta);
	
	return 0;
}
