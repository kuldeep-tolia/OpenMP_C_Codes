#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int id, x = 5;
	
	#pragma omp parallel private(id) firstprivate(x)
	{
		id = omp_get_thread_num();
		x = x + id;
		printf("private x: %d from thread: %d \n", x, id);
	}
	
	printf("after parallel region x: %d \n", x);
}
