// OpenMP parallelized jacobi iterative method solver
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#ifdef _OPENMP
#include <omp.h>
#endif

double S(double x)	{
	return (8.0 * x);
}

int main(int argc, char* argv[])	{
	
	int num_thread = 1;
	
	if(argc == 2)	{
		num_thread = strtol(argv[1], NULL, 10);
	}
	else	{
		printf("Command line argument of number of threads is required.\n");
		return 1;
	}
	
	double L = 1.0;	// Length of domain
	int N = 1000;		// Number of divisions
	
	// Allocate vectors
	double *xgrid = (double *)malloc((N+1) * sizeof(double));
	double *phi = (double *)malloc((N+1) * sizeof(double));
	double *phi_new = (double *)malloc((N+1) * sizeof(double));
	double *phi_exact = (double *)malloc((N+1) * sizeof(double));
	double *b = (double *)malloc((N+1) * sizeof(double));
	
	double dx, sum, comp_time;
	double residual, tolerance, global_error;
	int i, it_count;
	double t1, t2;
	FILE *fptr;
	
	dx = L / N;			// Grid numbering goes as 0:N
	tolerance = 1e-4;		// Set the tolerance criteria
	it_count = 0;
	residual = 0.0;
	sum = 0.0;
	global_error = 1.0;
	
	// Initialize vectors
	for(i = 0; i < (N+1); i++)	{
		xgrid[i] = i * dx;
		phi_exact[i] = (-4.0 * pow(xgrid[i], 3) + 1204.0 * xgrid[i] + 300.0) / 3.0;		// Analytical solution of given problem
		b[i] = dx * dx * S(xgrid[i]);		// Filling RHS known vector
		phi[i] = 100.0;			// Initial guess value for scalar field
		phi_new[i] = phi[i];
	}
	
	// Setting boundary conditions
	phi[0] = 100.0;		// Left side boundary
	phi[N] = 500.0;		// Right side boundary
	phi_new[0] = phi[0];
	phi_new[N] = phi[N];
	
	t1 = omp_get_wtime();
	#pragma omp parallel num_threads(num_thread) default(shared) private(i, residual)
	{
	while(global_error >= tolerance)	{
	
		sum = 0.0;
		
		// Jacobi iterative solver
		#pragma omp for
		for(i = 1; i < N; i++)	{
			phi_new[i] = (b[i] + phi[i-1] + phi[i+1]) / 2.0;
		}
	
		// Updating the vector
		#pragma omp for
		for(i = 1; i < N; i++)	{
			phi[i] = phi_new[i];
		}
	
		// Check residual, r = b - Ax
		#pragma omp for reduction(+: sum)
		for(i = 1; i < N; i++)	{
			residual = b[i] + phi[i-1] - 2.0 * phi[i] + phi[i+1];
			sum = sum + pow(residual, 2);
		}	
	
		// Monitors
		#pragma omp single
		{
			global_error = sqrt(sum);
			it_count++;
			if (it_count%1000 == 0)	{
				printf("#Iteration = %d, Error = %lf\n", it_count, global_error);
    			}
		}
	}
	}
	t2 = omp_get_wtime();
	comp_time = t2 - t1;
	
	// Post-processing
	fptr = fopen("parallel_solution_N_1000.txt", "w");
	for(i = 0; i < (N+1); i++)	{
		fprintf(fptr, "%lf  %lf  %lf\n", xgrid[i], phi_exact[i], phi[i]);
	}
	fclose(fptr);							
	
	printf("\n----------------------------\n");
	printf("Number of divisions = %d\n", N);
	printf("Total time taken for convergence = %lf seconds\n", comp_time);
	printf("Final global error = %lf\n", global_error);
	printf("Total iterations = %d\n", it_count);
	
	// Deallocate memory
	free(xgrid);
	free(phi);
	free(phi_new);
	free(phi_exact);
	free(b);
		
	return 0;
}
