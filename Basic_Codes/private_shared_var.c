#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int id;
	int x = 5;
	
	#pragma omp parallel private(x, id)
	{
		id = omp_get_thread_num();
		x = 3;
		x = x + id;
		printf("private x: %d from thread: %d \n", x, id);
	}
	
	printf("Value of x after parallel region: %d \n", x);
}
