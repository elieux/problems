#include <stdio.h>

typedef unsigned char Score;
typedef unsigned short int TotalScore;
typedef unsigned short int Throw;
typedef unsigned char Value;

Throw unique(Value values[5]) {
	Throw result = 0;
	unsigned int i, j, jMin;
	Value min;
	
	for (i = 0; 5 > i; i+= 1)
	{
		min = 7;
		for (j = 0; 5 > j; j+= 1)
			if (min > values[j])
			{
				jMin = j;
				min = values[j];
			}
		values[j] = 7;
		
		result *= 6;
		result += jMin;
	}
	
	return result;
}

#define THROW_MAX (1 << (8 * sizeof(Throw)))

int main(int argc, char *argv[]) {
	Value i1, i2, i3, i4, i5;
	Throw i;
	unsigned short int table[THROW_MAX];
	Value values[5];
	
	for (i1 = 1; 6 >= i1; i1 += 1)
	{
		values[0] = i1;
		for (i2 = 1; 6 >= i2; i2 += 1)
		{
			values[1] = i2;
			for (i3 = 1; 6 >= i3; i3 += 1)
			{
				values[2] = i3;
				for (i4 = 1; 6 >= i4; i4 += 1)
				{
					values[3] = i4;
					for (i5 = 1; 6 >= i5; i5 += 1)
					{
						values[4] = i5;
						table[unique(values)] += 1;
					}
				}
			}
		}
	}
	
	for (i = 0; THROW_MAX > i; i += 1)
		if (0 != table[i])
			printf("%4u: %4u\n", i, table[i]);
}