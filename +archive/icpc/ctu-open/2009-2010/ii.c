#include <stdio.h>
#include <string.h>

#define DEBUG
#define bool int
#define true 1
#define false 0

int num[10];
char input[11];

bool CheckValidity(void)
{
	char tmp[11];
	int slus=0,i = 0,k=0;
	long double temp; 
	memset(tmp, 11, sizeof(char));
	memset(num, 11, sizeof(int));
	
	

	for (i = 0; i < sizeof(input); i++)
	{
		if (slus==1)
			k=i-1;
		else
			k=i;
		
		switch(input[i]) {
			case '0' : num[k]=0;break;
			case '1' : num[k]=1;break;
			case '2' : num[k]=2;break;
			case '3' : num[k]=3;break;
			case '4' : num[k]=4;break;
			case '5' : num[k]=5;break;
			case '6' : num[k]=6;break;
			case '7' : num[k]=7;break;
			case '8' : num[k]=8;break;
			case '9' : num[k]=9;break;
			case '/' : {
				if ((((num[0]==5)&&(num[1]<=3))||(num[0]<=4))&&(num[0]>=1) )
					num[k]=0;
				else {
					slus = 1;
				}
				}break;
					
			
	        };
		
	}
	
	for (i=0;i<10;i++) 
	{
		switch(num[i]) {
			case 1:tmp[i]='1';break;
			case 2:tmp[i]='2';break;
			case 3 :tmp[i]='3';break;
			case 4:tmp[i]='4';break;
			case 5:tmp[i]='5';break;
			case 6:tmp[i]='6';break;
			case 7:tmp[i]='7';break;
			case 8:tmp[i]='8';break;
			case 9:tmp[i]='9';break;
			case 0:tmp[i]='0';break;
		};
	}
	sscanf(tmp, "%Lf", &temp);
	
	
#ifdef DEBUG
	   printf("Fuck: %s", tmp);
	   printf("Read int: %.0Lf ", temp);
	   printf("Num: %d%d%d%d%d%d%d%d%d%d",num[0],num[1],num[2],num[3],num[4],num[5],num[6],num[7],num[8],num[9]);
#endif
	

	if ( (int) temp % 11 == 0) 
		return true;
	else 
		return false;
		

	
   return false;
}

int IsBoy()
{
	int i=input[2];
	if ( (i>=1)&&(i<=12))
		return 0;
	else if ((i>=51)&&(i<=62))
		return 1;
	else 
		return 2;
	
	return 2;
}

int main()
{
	
	
	memset(input, 11, sizeof(char));
	
	do {
		fgets(input, 11, stdin);
		if (CheckValidity())
			switch (IsBoy()) {
				case 0 : printf("Boy\n");break;
				case 1: printf("Girl\n");break;
				case 2: printf("Invalid\n");break;
			}
		else
			printf("Invalid\n");
	} while (strcmp(input, "end\n" ) != 0);
	
	return 0;
}
