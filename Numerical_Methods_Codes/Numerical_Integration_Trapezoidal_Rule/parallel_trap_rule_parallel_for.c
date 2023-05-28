#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#ifdef _OPENMP
#include <omp.h>
#endif

#define PI 3.14159265358

double func(double x)	{
	return (1.0 + sin(x));		// given function to integrate
}

void trap_rule(double x_s, double x_e, int n, double *result)	{
	
	double h, x, partial_sum;
	int i;
	int thread_count = omp_get_num_threads();
	
	h = (x_e - x_s) / n;	
	partial_sum = (func(x_s) + func(x_e)) / 2.0;
	
	#pragma omp parallel num_threads(thread_count) reduction(+:partial_sum)
	{
		#pragma omp for
		for(i = 1; i <= n-1; i++)	{
				partial_sum = partial_sum + func(x_s + i * h);
			}
	}
	
	partial_sum = partial_sum * h;
	*result = partial_sum;
	
	return;
}

int main(int argc, char *argv[])	{

	double a, b, integration_result;
	int n;
	int num_thread = 1;
	
	if(argc == 2)	{
		num_thread = strtol(argv[1], NULL, 10);
	}
	else	{
		printf("Command line argument of number of threads is required.\n");
		return 1;
	}
	
	n = 72;	// number of divisions for integration
	a = 0.0;	// integration lower limit
	b = PI;	// integration upper limit
	integration_result = 0.0;	
	
	trap_rule(a, b, n, &integration_result);
	
	printf("\nThe integration for the given function between limits %lf and %lf = %lf.\n", a, b, integration_result);	

	return 0;
}
