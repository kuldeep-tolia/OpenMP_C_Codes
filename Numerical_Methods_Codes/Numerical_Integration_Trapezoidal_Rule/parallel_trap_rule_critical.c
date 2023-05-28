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

double trap_rule(double x_s, double x_e, int n)	{
	
	double h, x, partial_sum;
	int i;
	int my_id = omp_get_thread_num();
	int thread_count = omp_get_num_threads();
	int local_n;
	double local_a, local_b;
	
	h = (x_e - x_s) / n;
	
	local_n = n / thread_count;
	local_a = x_s + my_id * local_n * h;
	local_b = local_a + local_n * h;
	
	partial_sum = (func(local_a) + func(local_b)) / 2.0;
	
	for(i = 1; i <= local_n-1; i++)	{
		x = local_a + i * h;
		partial_sum = partial_sum + func(x);
	}
	
	partial_sum = partial_sum * h;
	
	return partial_sum;
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
	
	#pragma omp parallel num_threads(num_thread)	
	{	
		double local_sum;
		local_sum = trap_rule(a, b, n);
		#pragma omp critical
		integration_result = integration_result + local_sum;
	}
	
	printf("\nThe integration for the given function between limits %lf and %lf = %lf.\n", a, b, integration_result);	

	return 0;
}
