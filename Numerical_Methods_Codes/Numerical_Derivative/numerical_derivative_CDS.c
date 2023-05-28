#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#ifdef _OPENMP
#include <omp.h>
#endif

double dx = 0.001;		// Set delta-x parameter
double xstart = -1.0;		// Lower limit of domain
double xend = 1.0;		// Upper limit of domain

double f(double x)	{
	return (7.0 - x * tan(x));
}

double df(double x)	{
	return (-tan(x) - x / pow(cos(x), 2));
}

void initialize_vectors(int m, double *v1, double *v2, double *v3, double **v4)	{
	int i;
	for(i = 0; i < m; i++)	{
		v1[i] = xstart + i * dx;
		v2[i] = f(v1[i]);
		v3[i] = df(v1[i]);
		v4[0][i] = 0.0;
		v4[1][i] = 0.0;
	}
	return;
}

void cds_2order(int m, double *dudx, double *u, double exec_time, int nthread)	{
	int i;
	double t1, t2;
	
	// Calculate first derivative using forward/backward difference formulae near boundary points
	dudx[0] = (u[1] - u[0]) / dx;	
	dudx[m-1] = (u[m-1] - u[m-2]) / dx;
	
	t1 = omp_get_wtime();
	// Calculate first derivative using central difference formula 2nd order for interior points
	#pragma omp parallel for num_threads(nthread) default(shared) private(i)
	for(i = 1; i < m-1; i++)	{
		dudx[i] = (u[i+1] - u[i-1]) / (2.0 * dx);
	}
	t2 = omp_get_wtime();
	exec_time = t2-t1; 
	
	return;
}

void cds_4order(int m, double *dudx, double *u, double exec_time, int nthread)	{
	int i;
	double t1, t2;
	
	// Calculate first derivative using forward/backward/central difference formulae near boundary points
	dudx[0] = (u[1] - u[0]) / dx;	
	dudx[m-1] = (u[m-1] - u[m-2]) / dx;
	dudx[1] = (u[2] - u[0]) / (2.0 * dx);
	dudx[m-2] = (u[m-1] - u[m-3]) / (2.0 * dx);
	
	t1 = omp_get_wtime();
	// Calculate first derivative using central difference formula 4th order for interior points
	#pragma omp parallel for num_threads(nthread) default(shared) private(i)
	for(i = 2; i < m-2; i++)	{
		dudx[i] = (8.0 * u[i+1] - 8.0 * u[i-1] + u[i-2] - u[i+2]) / (12.0 * dx);
	}
	t2 = omp_get_wtime();
	exec_time = t2-t1; 
	
	return;
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
		
	int ndiv, n, i;
	double comp_time;
	FILE *fptr;
	
	ndiv = (xend - xstart) / dx;	// Number of divisions
	n = ndiv+1;			// Number of grid points (1:n)
	
	// Allocate vectors
	double *u = (double *)malloc(n * sizeof(double));
	double *xgrid = (double *)malloc(n * sizeof(double));
	double *dudx_exact = (double *)malloc(n * sizeof(double));
	double **dudx = (double **)malloc(2 * sizeof(double *));
	
	for(i = 0; i < 2; i++)	{
		dudx[i] = (double *)malloc(n * sizeof(double));
	}
	
	initialize_vectors(n, xgrid, u, dudx_exact, dudx);
	cds_2order(n, dudx[0], u, comp_time, num_thread);
	cds_4order(n, dudx[1], u, comp_time, num_thread);
	
	// Post-processing
	fptr = fopen("cds_dx2.txt", "w");
	for(i = 0; i < n; i++)	{
		fprintf(fptr, "%lf  %lf  %lf  %lf\n", xgrid[i], dudx_exact[i], dudx[0][i], dudx[1][i]);
	}
	fclose(fptr);
	
	printf("Number of threads = %d, dx = %lf\n", num_thread, dx);
	printf("Execution time = %lf seconds\n", comp_time);	
	
	// Deallocate vectors
	for(i = 0; i < 2; i++)	{
		free(dudx[i]);
	}
	
	free(dudx);
	free(dudx_exact);
	free(xgrid);
	free(u);	
	return 0;
}
