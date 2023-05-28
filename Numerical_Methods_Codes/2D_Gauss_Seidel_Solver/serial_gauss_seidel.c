// Serial program to solve given Poisson equation using Gausss-Seidel method
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void initialize_grid(double *xgrid, double *ygrid, double delta, double xmin, double ymin, int n)	{
	xgrid[0] = xmin;
	ygrid[0] = ymin;
	for(int i = 1; i < (n+1); i++)	{
		xgrid[i] = xgrid[i-1] + delta;
		ygrid[i] = ygrid[i-1] + delta;
	}
	return;
}

double analytical_sol(double x, double y)	{
	return ((pow(x, 2.0) - 1.0) * (pow(y, 2.0) - 1.0));
}

int main(int argc, char* argv[])	{
	
	double delta = 0.01;		// grid spacing, assumed delta_x = delta_y = delta
	int i, j, N, it_count;
	double xmin, xmax, ymin, ymax;
	double tolerance, global_error;
	clock_t t1, t2;
	FILE *fptr;
	
	// Set domain extent
	xmin = -1.0;
	xmax = 1.0;
	ymin = -1.0;
	ymax = 1.0;
	
	N = (xmax - xmin) / delta;	// Number of grid points required in x, y directions	NOTE: grid numbering goes as 0:N
	tolerance = 1e-6;		// Set tolerance value
	global_error = 1.0;
	it_count = 0;
	
	printf("N = %d, delta = %lf\n", N, delta);
	
	// Allocate vectors
	double *xgrid = (double *)malloc((N+1) * sizeof(double));
	double *ygrid = (double *)malloc((N+1) * sizeof(double));
	
	// Allocate matrices
	double **phi = (double **)malloc((N+1) * sizeof(double));
	double **q = (double **)malloc((N+1) * sizeof(double));
	double **phi_exact = (double **)malloc((N+1) * sizeof(double));
	double **domain_error = (double **)malloc((N+1) * sizeof(double));
	
	for(j = 0; j < (N+1); j++)	{
		phi[j] = (double *)malloc((N+1) * sizeof(double));
		q[j] = (double *)malloc((N+1) * sizeof(double));
		phi_exact[j] = (double *)malloc((N+1) * sizeof(double));
		domain_error[j] = (double *)malloc((N+1) * sizeof(double));
	}
	
	t1 = clock();
	// Initialize grid
	initialize_grid(xgrid, ygrid, delta, xmin, ymin, N);

	// Calculate given analytical solution, source term and initialize the scalar field
	for(i = 0; i < N+1; i++)	{
		for(j = 0; j < N+1; j++)	{
			phi_exact[i][j] = analytical_sol(xgrid[i], ygrid[j]);
			q[i][j] = 2.0 * (2.0 - pow(xgrid[i], 2.0) - pow(ygrid[j], 2.0));
			phi[i][j] = 0.0;		// Initialize the domain with guess value
		}
	}
	
	// Set boundary conditions
	for(i = 0; i < N+1; i++)	{
		phi[i][0] = 0.0;	// Bottom boundary
		phi[i][N] = 0.0;	// Top boundary
	}
	
	for(j = 0; j < N+1; j++)	{
		phi[0][j] = 0.0;	// Left boundary
		phi[N][j] = 0.0;	// Right boundary
	}
	
	while (global_error >= tolerance)	{
		
		// Gauss-Seidel iterative solver
		for(i = 1; i < N; i++)	{
			for(j = 1; j < N; j++)	{
				phi[i][j] = 0.25 * (phi[i+1][j] + phi[i-1][j] + phi[i][j+1] + phi[i][j-1]) \
					    + (q[i][j] * 0.25 * delta * delta);
				
				domain_error[i][j] = fabs((phi_exact[i][j] - phi[i][j]) / phi_exact[i][j]);
			}
		}
		
		// Calculate global error by taking max-norm of error-matrix
		global_error = domain_error[1][1];
		for(i = 1; i < N; i++)	{
			for(j = 1; j < N; j++)	{
				if (global_error < domain_error[i][j])	{
					global_error = domain_error[i][j];
				}
			}
		}
		
		// Monitors
		it_count++;
		if (it_count%10 == 0)	{
			printf("#Iteration = %d, Global error = %lf\n", it_count, global_error);
		}
	}
	t2 = clock();
	
	// Post-processing
	fptr = fopen("phi_profile_y_05.txt", "w");
	for(i = 0; i < (N+1); i++)	{
		fprintf(fptr, "%lf  %lf  %lf\n", xgrid[i], phi_exact[i][3*N/4], phi[i][3*N/4]);
	}
	fclose(fptr);	
	
	printf("\n----------------------------\n");
	printf("Total time taken for convergence = %lf\n", ((double)(t2-t1) / CLOCKS_PER_SEC));
	printf("Final global error = %lf\n", global_error);
	printf("Total iterations taken for convergence = %d\n", it_count);
	
	// Deallocate memory
	for(i = 0; i < N+1; i++)	{
		free(phi_exact[i]);
		free(phi[i]);
		free(q[i]);
		free(domain_error[i]);
	}
	free(xgrid);
	free(ygrid);
	free(phi);
	free(q);
	free(phi_exact);
	free(domain_error);
		
	return 0;
}
