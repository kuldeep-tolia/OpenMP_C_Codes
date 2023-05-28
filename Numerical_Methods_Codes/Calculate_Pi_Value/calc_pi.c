#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#ifdef _OPENMP
#include <omp.h>
#endif

#define N 100000000

int main(int argc, char *argv[])	{

	int num_thread = 1;
	int k;
	double sign = 1.0, sum = 0.0, pi = 0.0, start, end;
	
	if(argc == 2)	{
		num_thread = strtol(argv[1], NULL, 10);
	}
	else	{
		printf("Command line argument of number of threads is required.\n");
		return 1;
	}
	
	start = omp_get_wtime();
	#pragma omp parallel num_threads(num_thread) reduction(+:sum) default(shared) private(k, sign)
	{
	#pragma omp for
	for(k = 0; k < N; k++)	{
			if(k % 2 == 0)
				sign = 1.0;
			else
				sign = -1.0;
			sum = sum + (sign / (2.0 * k + 1.0));
		}
	}
	end = omp_get_wtime();
	
	pi = 4.0 * sum;
	printf("Approximate value of PI using series expansion is %0.8lf\n", pi);
	printf("Execution time = %lf seconds\n", end-start);
	
	return 0;
}
