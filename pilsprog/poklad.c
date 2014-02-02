#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define true 1
#define false 0
#define MAXT 720
#define MAXL 840
#define MAXB 120
#define abs(x) ((x < 0) ? -x : x)

int fnd(const int a[6], const int n)
{
	int i;
	
	for (i = 0; i < 6; i++)
	{
		if (a[i] == n)
			return i;
	}
	return -1;
}

int cmp(const int a[6], const int b[6])
{
	if (memcmp(a, b, 6 * sizeof(int)) == 0)
		return true;
	return false;
}

int dff(const int a[6], const int b[6])
{
	int i;
	
	for (i = 0; i < 6; i++)
		if ((a[i] != b[i]) && (a[i] != 0))
			return a[i];
	return -1;
}

void abl(const int a[6], int r[3])
{
	int c;
	
	for (c = 0; c < 3; c++)
		r[c] = -1;
	c = fnd(a, 0);
	if (c <= 2)
		r[0] = a[c + 3];
	if (c >= 3)
		r[0] = a[c - 3];
	if (((c % 3) == 0) || ((c % 3) == 1))
		r[1] = a[c + 1];
	if (((c % 3) == 1) || ((c % 3) == 2))
		r[2] = a[c - 1];
}

void swt(int a[6], const int n)
{
	int c, d;
	
	c = fnd(a, n);
	d = fnd(a, 0);
	if (((c <= 2) && (d >= 3) && ((d - c) == 3)) || ((d <= 2) && (c >= 3) && ((c - d) == 3)) || ((d <= 2) && (c <= 2) && (abs(c - d) == 1)) || ((d >= 3) && (c >= 3) && (abs(c - d) == 1)))
	{
		a[c] = 0; a[d] = n;
		return;
	}
}

void pop(int a[MAXT][6], int la[MAXL], int lb[MAXL],  int lc[MAXL])
{
	int i, j, k, l, m, n, c;
	int r[3];
	int tmp[6];
	
	c = 0;
	for (i = 0; i < 6; i++)
		for (j = 0; j < 6; j++)
			if (i != j)
				for (k = 0; k < 6; k++)
					if ((k != i) && (k != j))
						for (l = 0; l < 6; l++)
							if ((l != i) && (l != j) && (l != k))
								for (m = 0; m < 6; m++)
									if ((m != i) && (m != j) && (m != k) && (m != l))
										for (n = 0; n < 6; n++)
											if ((n != i) && (n != j) && (n != k) && (n != l) && (n != m))
											{
												a[c][0] = i;
												a[c][1] = j;
												a[c][2] = k;
												a[c][3] = l;
												a[c][4] = m;
												a[c][5] = n;
												c++;
											}
	c = 0;
	for (i = 0; i < MAXT; i++)
	{
		memcpy(tmp, a[i], 6 * sizeof(int));
		abl(tmp, r);
		for (j = 0; j < 3; j++)
			if (r[j] != -1)
			{
				swt(tmp, r[j]);
				for(k = i + 1; k < MAXT; k++)
					if (cmp(tmp, a[k]))
					{
						la[c] = i;
						lb[c] = k;
						lc[c] = r[j];
						c++;
					}
			}
	}
	/**/printf("%d !!\n", c);
}

int srch(const int a[MAXT][6], const int b[6])
{
	int i;
	
	for (i = 0; i < MAXT; i++)
	{
		if (cmp(a[i], b))
		{
			return i;
		}
	}
	return -1;
}

int srchi(const int a[MAXB], const int n)
{
	int i;
	
	for (i = 1; i <= a[0]; i++)
		if (a[i] == n)
			return true;
	return false;
}

int main()
{
	const int win[6] = {1, 2, 3, 4, 5, 0};
	int map[6], a, b, c, i, from, to, wini;
	int r[3];
	int t[MAXT][6];
	int la[MAXL], lb[MAXL], lc[MAXL];
	int **buf;
	int tmpwin[MAXB], tmp[MAXB], /**/*test;
	
/*	for (i = 0; i < 2; i++)
	{
		scanf("%d %d %d", &a, &b, &c);
		map[3 * i] = a;
		map[3 * i + 1] = b;
		map[3 * i + 2] = c;
	}*/map[0] = 0; map[1] = 5; map[2] = 2; map[3] = 1; map[4] = 4; map[5] = 3;
	
	swt(map, 3);
	printf("debug!\n");
/**/printf("%d %d %d\n%d %d %d\n--\n", map[0], map[1], map[2], map[3], map[4], map[5]);
/*	abl(map, r);
	for (i = 0; i < 3; i++)
		printf("%d\n", r[i]);*/
	pop(t, la, lb, lc);
/**/printf("jede\n");
/*	for (i = 0; i < 5; i++)
	{
		printf("%d %d %d\n%d %d %d\n->\n%d %d %d\n%d %d %d\n\n", t[la[i]][0], t[la[i]][1], t[la[i]][2], t[la[i]][3], t[la[i]][4], t[la[i]][5], t[lb[i]][0], t[lb[i]][1], t[lb[i]][2], t[lb[i]][3], t[lb[i]][4], t[lb[i]][5]);
	}*/
	
	b = -1;
	buf = malloc(MAXL * sizeof(int *));
	buf[++b] = malloc(MAXB * sizeof(int));
	buf[b][0] = 0;
	buf[b][++buf[b][0]] = srch(t, map);
	tmpwin[0] = MAXB;
	wini = srch(t, win);
/**/printf("jede1 wini = %d\n", wini);
/*for (b = 0; b < 100; b++) {printf("alokuju element %d", b); buf[b] = malloc(MAXB * sizeof(int)); printf("-ok\n");} b = 0;*/
	while (b >= 0)
	{
		memcpy(tmp, buf[b], MAXB * sizeof(int));
		free(buf[b--]);
		if (tmp[tmp[0]] == wini)
		{
			if (tmp[0] < tmpwin[0])
				memcpy(tmpwin, tmp, MAXB * sizeof(int));
		}
		else
		{
			for (a = 0; a < MAXL; a++)
			{
				from = tmp[0];
				if ((la[a] == from) || (lb[a] == from))
				{
					if (la[a] == from)
						to = lb[a];
					if (lb[a] == from)
						to = la[a];
					if (!srchi((int *) tmp, to))
					{
						tmp[++tmp[0]] = to;
/**/printf("jede b = %2d-1", b);
						test = malloc(MAXB * sizeof(int));
/**/printf("-2");
						buf[++b] = test;
/**/printf("-3\n");
						memcpy(buf[b], tmp, MAXB * sizeof(int));
						tmp[0]--;
					}
				}
			}
		}
	}
/**/printf("jede3\n");
	
	for (i = 0; i < tmpwin[0]; i++)
	{
		printf("%d %d %d\n%d %d %d\n->\n", t[i][0], t[i][1], t[i][2], t[i][3], t[i][4], t[i][5]);
	}
	
	return 0;
}
