#ifdef _OPENMP
#include <omp.h>
#endif
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int thread_count = 1;
	
	if(argc == 2)	{
		thread_count = strtol(argv[1], NULL, 10);
	}
	else	{
		printf("Command line argument of number of threads is required.\n");
		return 1;
	}
	
	#pragma omp parallel num_threads(thread_count)
	{
		#ifdef _OPENMP
		int id = omp_get_thread_num();
		int total_threads = omp_get_num_threads();
		#else
		int id = 0;
		int total_threads = 1;
		#endif

		printf("Hello World from thread id %d out of total threads %d\n", id, total_threads);
	}
	
	return 0;
}
