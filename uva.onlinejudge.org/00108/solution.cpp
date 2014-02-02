#include <iostream>
#include <algorithm>

typedef unsigned int uint;

int sum1(int *matrix, uint n, uint r0, uint r1, uint c0, uint c1) {
	int sum = 0;
	
	for (uint r = r0; r <= r1; r++)
		for (uint c = c0; c <= c1; c++)
			sum += matrix[r * n + c];
	
	return sum;
}

int sum(int *matrix, uint n, uint r0, uint r1, uint c0, uint c1) {
	int sum = 0;
	
	uint r1n = r1 * n;
	for (uint rn = r0 * n; rn <= r1n; rn += n)
	{
		uint rnc1 = rn + c1;
		for (uint rnc = rn + c0; rnc <= rnc1; rnc++)
			sum += matrix[rnc];
	}
	
	return sum;
}

int solve(int *matrix, uint n) {
	int *rowsums = new int[n * (n + 1)]();
	
	for (uint r = 0; r < n; r++)
		for (uint c = 0; c <= n; c++)
			rowsums[r * n + c + 1] = rowsums[r * n + c] + matrix[r * n + c];
	
	int max = matrix[0 * n + 0];
	
	for (uint c0 = 0; c0 < n; c0++)
		for (uint c1 = c0 + 1; c1 <= n; c1++)
		{
			int running_sum = 0;
			for (uint r = 0; r < n; r++)
			{
				int element = rowsums[r * n + c1] - rowsums[r * n + c0];
				if (running_sum < 0)
					running_sum = 0;
				running_sum += element;
				max = std::max(max, running_sum);
			}
		}
	
	delete[] rowsums;
	
	return max;
}

int main() {
	uint n;
	std::cin >> n;
	
	int *matrix = new int[n * n];
	
	for (uint r = 0; r < n; r++)
		for (uint c = 0; c < n; c++)
			std::cin >> matrix[r * n + c];
	
	std::cout << solve(matrix, n) << std::endl;
	
	delete[] matrix;
	
	return 0;
}
