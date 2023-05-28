#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#ifdef _OPENMP
#include <omp.h>
#endif

#define N 20

int fib(int n)	{
	int i, j;
	if(n < 2) 
		return n;
	else    {
		#pragma omp task shared(i)
			i = fib(n-1);
		#pragma omp task shared(j)
			j = fib(n-2);
		#pragma omp taskwait
		return (i + j);
	}
}

int main(int argc, char *argv[])	{

	int num_thread = 1;
	int my_id;
	
	if(argc == 2)	{
		num_thread = strtol(argv[1], NULL, 10);
	}
	else	{
		printf("Command line argument of number of threads is required.\n");
		return 1;
	}
	
	#pragma omp parallel num_threads(num_thread) private(my_id)	
	{
		#pragma omp single
		{
			my_id = omp_get_thread_num();
			for(int i = 0; i <= N; i++)	{
				printf("fib(%d) = %d by %d\n", i, fib(i), my_id);
			}
		}
	}

	return 0;
}
