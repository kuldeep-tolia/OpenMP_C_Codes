#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int i, id;
	static int ia;
	
	#pragma omp threadprivate(ia)
	omp_set_num_threads(4);
	
	#pragma omp parallel private(i, id)
	{
		id = omp_get_thread_num();
		#pragma omp for
		for(i = 0; i < 8; i++)
		{
			ia = id + i;
			printf("ia = %d for i = %d from id = %d \n", ia, i, id);
		}
		
		#pragma omp for
		for(i = 0; i < 8; i++)
		{
			ia = ia + i;
			printf("ia = %d for i = %d from id = %d \n", ia, i, id);
		}
	}
}
