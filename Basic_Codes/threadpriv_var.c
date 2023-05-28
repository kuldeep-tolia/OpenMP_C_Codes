#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int id;
	static int x;
	
	#pragma omp threadprivate(x)
	#pragma omp parallel private(id)
	{
		id = omp_get_thread_num();
		x = x + id;
		printf("private x: %d from thread: %d \n", x, id);
	}
	
	#pragma omp parallel private(id)
	{
		id = omp_get_thread_num();
		x = x + 10;
		printf("2nd parallel x: %d from thread: %d \n", x, id);
	}
}
