#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define LINE_LENGTH 1024
#define PI 3.1415
#define torad(x) ((x*PI)/180)
#define len 22

bool big;

int bigA[2][len];

void init(char clockface[51][51])
{

	for (int i = 0; i < 51; i++)
		{
			if ((i%10)==0)
			{
					clockface[0][i] = '@';
					clockface[50][i] = '@';
					clockface[i][50] = '@';
					clockface[i][0] = '@';
			
			}
			else
			{
					clockface[0][i] = 'X';
					clockface[50][i] = 'X';
					clockface[i][50] = 'X';
					clockface[i][0] = 'X';
			}
		}
			
	for (int i = 1; i < 50; i++)
		for (int j = 1; j < 50; j++)
			clockface[i][j] = ' ';
		
	clockface [25][2] = '9';
	clockface[25][48] = '3';
	clockface[2][24] = '1';
	clockface[2][26] = '2';
	clockface[48][25] = '6';
	clockface[25][25] = '*';
	
}

void print_out(char clockface[51][51])
{
	for (int i = 0; i < 51; i ++)
	{
		for (int j = 0; j < 51; j++)
			printf("%c", clockface[i][j]);
		printf("\n");
	}
	
}
void modify_pic(char clockface[51][51] , char cf_fin[51][51]);


void tle() {
	while (1);
}

void doit() {
}

void draw_min(char clockface[51][51], int q, char cf_fin[51][51])
{
	int length;
	if (big)
		length = 21;
	else 
		length =15;
	switch (q)
	{
		case 1:
		{for (int i = 0; i < length; i++)
			clockface[24-bigA[0][i]][26+bigA[1][i]] = 'C';
			break;
		}
		case 2:
		{for (int i = 0; i < length; i++)
			clockface[26+bigA[0][i]][26+bigA[1][i]] = 'C';
			break;
		}
		case 3:
		{for (int i = 0; i < length; i++)
			clockface[26+bigA[0][i]][24-bigA[1][i]] = 'C';
		break;
			}
		case 4:
		{for (int i = 0; i < length; i++)
			clockface[24-bigA[0][i]][24-bigA[1][i]] = 'C';
		break;
			}
	}
	

		
	modify_pic (clockface, cf_fin);
	//init (clockface);
}


void doMin(int ang, char clockface[51][51], char cf_fin[51][51])
{
	int q = (ang/90)+1;
	ang = ang%90;
	double rad = ang*PI/180;
	printf("uhel %d\n", ang);
	double tang = tan(rad);
	printf ("uhel v radianech %f, tangenta %f\n", rad, tang);
	if (ang == 0)
		for (int i = 0; i < len; i++)
		{
			bigA[0][i] = i;
			bigA[1][i] = 0;
		}
	if (ang ==45)
		for (int i = 0; i < len; i++)
		{
			bigA[0][i] = i;
			bigA[1][i] = i;
		}if (ang == 90)
		for (int i = 0; i < len; i++)
		{
			bigA[0][i] = 0;
			bigA[1][i] = i;
		}
	if ((ang > 0) && (ang < 45))
		for (int i = 0; i < len; i++)
		{
			bigA[0][i] = i;
			double aux = tang*i;
			if ((aux-ceil(aux)) >= 0.5)
				bigA[1][i] = floor(aux);
			else
				bigA[1][i] = ceil(aux);
			printf ("bigA = %d, %d\n", bigA[0][i], bigA[1][i]);
		}
	if ((ang > 45) && (ang < 90))
		for (int i = 0; i < len; i++)
		{
			bigA[1][i] = i;
			double aux = tang*i;
			if ((aux-ceil(aux)) >= 0.5)
				bigA[0][i] = floor(aux);
			else
				bigA[0][i] = ceil(aux);
			printf ("bigA = %d, %d\n", bigA[0][i], bigA[1][i]);
		}
		
	draw_min(clockface,q, cf_fin);	
}

int main(int argc, char *argv[]) {
	char line[LINE_LENGTH];
	char clockface[51][51];
	char cf_fin[51][51];
	argc = argc;
	argv = argv;
	int hour, min;
	init(clockface);
	
	
/*	while (true)*/
	{
		hour = (getchar()-'0')*10;
		hour += (getchar()-'0');
		getchar();
		min = (getchar()-'0')*10;
		min += (getchar()-'0');
		big = true;
		double mAng = min*6;
		
		double hAng = (hour*6+(min/3600));
		
		doMin(mAng, clockface, cf_fin);
		big = false;
		doMin(hAng, clockface, cf_fin);
		
		doit();
		
		//~ if ()
			//~ break;
	}


	//*************8
	//double mAng = 18;
	//doMin(mAng, clockface, cf_fin);
//	double hAng = 
	
	//*************8
	modify_pic(clockface, cf_fin);
	
	
	print_out(cf_fin);
	
	return 0;
}

void modify_pic(char clockface[51][51] , char cf_fin[51][51])
{
	init (cf_fin);
	for (int i = 0; i <51; i++)
		for (int j = 0; j <51; j++)
			if (clockface[i][j] == 'C')
				if (clockface[i][j-1] == 'C' && clockface[i][j+1]=='C')
					cf_fin[i][j] = '-';
				else
					if (clockface[i-1][j] == 'C' && clockface[i+1][j]=='C')
						cf_fin[i][j] = '|';
					else 
						if (clockface[i+1][j-1] == 'C' && clockface[i-1][j+1]=='C')
							cf_fin[i][j] = '\\';
						else 
							if (clockface[i-1][j-1] == 'C' && clockface[i+1][j+1]=='C')
								cf_fin[i][j] = '/';
							else cf_fin[i][j] = 'o';
				
}

