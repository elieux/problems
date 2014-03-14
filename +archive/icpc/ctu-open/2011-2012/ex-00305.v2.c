#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int f(int k)
{
   int m, n, p, r;

   for (n = 2 * k, m = 2;; m++) {
      for (p = 0, r = n; r > k; r--)
         if ((p = (p + m - 1) % r) < k) break;
      if (r == k) return m;
   }
}

int main(int argc, char *argv[]) {
	char buffer[32];
	int cislo;
	
	do {
		fgets(buffer, 32, stdin);
		sscanf(buffer, "%d", &cislo);
		
		if (cislo == 0)
			break;
		
		printf("%d\n", f(cislo));
	} while (true);
	
	return 0;
}
