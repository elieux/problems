#include <stdio.h>
#define false 0
#define true 1
#define A 1
#define B 2

int main()
{
	int c, i, n, l, o, t;
	short int a[40000], b[40000], p[40000], v[199];
	
	scanf("%d", &n);
	scanf("%d", &l);
	for (i = 1; i <= l; i++)
	{
		scanf("%d %d", &a[i], &b[i]);
		p[i] = 0;
	}
	
	v[0] = A;
	for (i = 1; i < n; i++)
		v[i] = 0;
	
	o = true;
	c = true;
	do
	{
		t = 0;
		for (i = 1; i <= l; i++)
		{
			if (!p[i])
			{
				t++;
				p[i] = 1;
				if (v[a[i]])
				{
					if (v[b[i]] && (v[b[i]] == v[a[i]]))
					{
						o = false;
						c = false;
					}
					else
						v[b[i]] = ((v[a[i]] == A) ? B : A);
				}
				if (v[b[i]])
				{
					v[a[i]] = ((v[b[i]] == A) ? B : A);
				}
			}
		}
		if (t == 0)
			c = false;
	}
	while (c);
	printf((o ? "Lze obarvit\n" : "Nelze obarvit\n"));
	
	return 0;
}
