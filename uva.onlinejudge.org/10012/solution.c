#include <stdio.h>
#include <string.h>
#include <math.h>

#undef PLOT

#define LINE_LENGTH 256
#define CIRCLES_MAX 8

typedef struct {
	double x, r;
} Circle;

typedef Circle Circles[CIRCLES_MAX];

#define UNDEFINED -13

void switcheroo(double *a, double *b) {
	double t;
	t = *a;
	*a = *b;
	*b = t;
}

double getX(Circle oldCircle, Circle newCircle) {
	return oldCircle.x + sqrt(pow(oldCircle.r + newCircle.r, 2) - pow(oldCircle.r - newCircle.r, 2));
}

void solveCircles(Circles circles, unsigned int remaining, double result, double *bestResult, Circles *bestCircles) {
	unsigned int i;
	double minX, width;
	
	remaining--;
	
	minX = circles[remaining].r;
	for (i = remaining + 1; CIRCLES_MAX > i; i++)
	{
		if (UNDEFINED == circles[i].r)
			continue;
		if (minX < (width = getX(circles[i], circles[remaining])))
			minX = width;
	}
	circles[remaining].x = minX;
	if (result < (width = circles[remaining].x + circles[remaining].r))
		result = width;
	
	if (0 == remaining)
	{
		if (UNDEFINED == *bestResult || *bestResult > result)
		{
			*bestResult = result;
#ifdef PLOT
			for (i = 0; CIRCLES_MAX > i; i++)
			{
				(*bestCircles)[i].x = circles[i].x;
				(*bestCircles)[i].r = circles[i].r;
			}
#endif
		}
		return;
	}
	if (UNDEFINED != *bestResult && *bestResult < result)
		return;
	for (i = 0; remaining > i; i++)
	{
		switcheroo(&circles[remaining - 1].x, &circles[i].x);
		switcheroo(&circles[remaining - 1].r, &circles[i].r);
		
		solveCircles(circles, remaining, result, bestResult, bestCircles);
		
		switcheroo(&circles[remaining - 1].x, &circles[i].x);
		switcheroo(&circles[remaining - 1].r, &circles[i].r);
	}
}

int main(int argc, char *argv[]) {
	unsigned int i, j;
	unsigned int nCases, nCircles;
	char line[LINE_LENGTH];
	Circles circles, bestCircles;
	double width;
	
	argc = argc; argv = argv;
	
	do
		fgets(line, LINE_LENGTH, stdin);
	while (1 != sscanf(line, "%u", &nCases));
	
	for (i = 0; nCases > i; i++)
	{
		for (j = 0; CIRCLES_MAX > j; j++)
		{
			circles[j].x = UNDEFINED;
			circles[j].r = UNDEFINED;
			bestCircles[j].x = UNDEFINED;
			bestCircles[j].r = UNDEFINED;
		}
		
		do
			fgets(line, LINE_LENGTH, stdin);
		while (1 != sscanf(line, "%u", &nCircles));
		
		sscanf(&(line[2]), "%lf %lf %lf %lf %lf %lf %lf %lf", &circles[0].r, &circles[1].r, &circles[2].r, &circles[3].r, &circles[4].r, &circles[5].r, &circles[6].r, &circles[7].r);
		
		width = UNDEFINED;
		for (j = 0; nCircles > j; j++)
		{
			switcheroo(&circles[nCircles - 1].x, &circles[j].x);
			switcheroo(&circles[nCircles - 1].r, &circles[j].r);
			
			solveCircles(circles, nCircles, 0.0l, &width, &bestCircles);
			
			switcheroo(&circles[nCircles - 1].x, &circles[j].x);
			switcheroo(&circles[nCircles - 1].r, &circles[j].r);
		}
#ifdef PLOT
		printf("plot ");
		for (j = 0; nCircles > j; j++)
		{
			if (0 < j)
				printf(", ");
			printf("%f + %f * sin(t), %f + %f * cos(t)\\\n", bestCircles[j].x, bestCircles[j].r, bestCircles[j].r, bestCircles[j].r);
		}
#endif
		printf("%.3f\n", width);
	}
	
	return 0;
}
