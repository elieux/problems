#include <cstdio>
#include <cstring>
#include <cmath>

#define PI (4.0L*(atanl(1.0L)))
#define PIx (4.0*(atan(1.0)))

typedef long double numbertype;
#define FORMAT "Lf"
typedef unsigned int uint;

numbertype dist(numbertype x1, numbertype y1, numbertype x2, numbertype y2)
{
	return sqrt(pow(y2-y1, 2) + pow((x2 - x1), 2));
}

numbertype degree(numbertype x1, numbertype y1, numbertype x2, numbertype y2)
{
	if (x1 == x2)
		return 0.0L;
	
	numbertype neco = atan((y2-y1)/(x2-x1));
	//~ printf("neco:: %Lf\n", neco);
	if (neco < 0.0L)
		neco += PI;
	
	
	//~ printf("neco:: %Lf\n", neco);
	
	return 180.0L*neco/PI;
}

int main(int argc, char *argv[]) {
	
	numbertype S, T;
	numbertype X1, X2, Y1, Y2;
	
	while (scanf("%" FORMAT " %" FORMAT "", &S, &T) == 2) {
		scanf("%" FORMAT " %" FORMAT " %" FORMAT " %" FORMAT "", &X1, &Y1, &X2, &Y2);
		numbertype L = dist(X1, Y1, X2, Y2);
		numbertype D = degree(X1, Y1, X2, Y2);
		printf("%.4" FORMAT "\n", L/S + D/T);
	}
	
	return 0;
}
