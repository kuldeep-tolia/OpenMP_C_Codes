#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int id;
//	omp_set_nested(1);
	omp_set_num_threads(2);
	#pragma omp parallel private(id)
	{
		id = omp_get_thread_num();
		printf("Hello from thread = %d \n", id);
		#pragma omp parallel private(id)
		{
			id = omp_get_thread_num();
			printf("HI from thread = %d \n", id);
		}
	}
}
