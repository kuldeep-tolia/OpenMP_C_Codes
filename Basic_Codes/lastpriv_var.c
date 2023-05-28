#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int id, i, a;
	
	#pragma omp parallel for private(i, id) lastprivate(a)
	for(i = 0; i < 12; i++)
	{
		id = omp_get_thread_num();
		a = i + 1;
		printf("a: %d for i: %d from thread: %d \n", a, i, id);
	}
	
	printf("after parallel region a: %d \n", a);
}
