#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define Ndim 10000000
#define num_threads 8

int main(int argc, char **argv)
{
	int i, j, k;
	double *A, *B, C = 0, cval, tmp, err, errsq;
	double dN, mflops;
	double start_time, end_time;
	A = (double *)malloc(Ndim * sizeof(double));
	B = (double *)malloc(Ndim * sizeof(double));
	
	for (i = 0; i < Ndim; i++)
	{
		*(A+i) = 1.0;
		*(B+i) = 1.0;
	}
	
	omp_set_num_threads(num_threads);
	start_time = omp_get_wtime();
	
	#pragma omp parallel for reduction(+:C) private (i) default (shared)
	for(i = 0; i < Ndim; i++)
	{
		C += *(A+i) * *(B+i);
	}
	
	end_time = omp_get_wtime() - start_time;
	printf("number of threads = %d\n", num_threads);
	printf("Order %d multiplication in %f seconds \n", Ndim, end_time);
	cval = Ndim;
	err = C - cval;
	errsq = err * err;
	printf("\nerror in multiplication = %f\n", errsq);
}
	
	
