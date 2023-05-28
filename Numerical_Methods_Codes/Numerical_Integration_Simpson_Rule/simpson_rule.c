#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#ifdef _OPENMP
#include <omp.h>
#endif

#define PI 3.14159265358
#define I 0.198573

double func(double x)	{
	return (sin(x) / (2.0 * pow(x, 3)));		// given function to integrate
}

void trap_rule(double x_s, double x_e, int n, double *result)	{
	
	double h, x, partial_sum;
	int i;
	int thread_count = omp_get_num_threads();
	
	h = (x_e - x_s) / n;	
	partial_sum = (func(x_s) + func(x_e));
	
	#pragma omp parallel num_threads(thread_count) reduction(+:partial_sum)
	{
		#pragma omp for
		for(i = 1; i <= n-1; i=i+2)	{
			partial_sum = partial_sum + 4.0 * func(x_s + i * h);
		}
		
		#pragma omp for
		for(i = 2; i <= n-2; i=i+2)	{
			partial_sum = partial_sum + 2.0 * func(x_s + i * h);
		}		
	}
	
	partial_sum = partial_sum * h / 3.0;
	*result = partial_sum;
	
	return;
}

int main(int argc, char* argv[])	{
	
	double a, b, integration_result, error;
	int n;
	int num_thread = 1;
	
	if(argc == 2)	{
		num_thread = strtol(argv[1], NULL, 10);
	}
	else	{
		printf("Command line argument of number of threads is required.\n");
		return 1;
	}
	
	n = 32;	// number of divisions for integration
	a = 1.0;	// integration lower limit
	b = PI;	// integration upper limit
	integration_result = 0.0;
	
	trap_rule(a, b, n, &integration_result);
	
	error = fabs(I - integration_result);
	printf("\nNumber of threads = %d, Number of Simpson divisions = %d\n", num_thread, n);	
	printf("The integration for the given function between limits 1.0 and PI = %lf.\n", integration_result);	
	printf("Absolute error with the exact integration value = %lf.\n", error);
		
	return 0;
}
