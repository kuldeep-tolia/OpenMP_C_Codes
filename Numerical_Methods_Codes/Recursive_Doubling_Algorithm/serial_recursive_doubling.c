// Serial program to calculate first derivative using recursive double method
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double func(double x)	{
	return (sin(5.0 * x));
}

double dfunc(double x)	{
	return(5.0 * cos(5.0 * x));
}

int main(int argc, char* argv[])	{
	
	int N = 1000;			// Number of divisions
	double Lx = 3.0;		// Length of domain
	
	// Allocate vectors
	double *xgrid = (double *)malloc((N+2) * sizeof(double));
	double *f = (double *)malloc((N+2) * sizeof(double));
	double *x = (double *)malloc((N+2) * sizeof(double));
	double *df_exact = (double *)malloc((N+2) * sizeof(double));
	double *a = (double *)malloc((N+2) * sizeof(double));
	double *b = (double *)malloc((N+2) * sizeof(double));
	double *c = (double *)malloc((N+2) * sizeof(double));
	double *d = (double *)malloc((N+2) * sizeof(double));
	double *alpha = (double *)malloc((N+2) * sizeof(double));
	double *beta = (double *)malloc((N+2) * sizeof(double));
	
	double h, comp_time;
	int i, k, k_steps;
	clock_t t1, t2;
	FILE *fptr;

	h = Lx / N;	// grid spacing
	k_steps = ceil(log(N+1.0)/log(2.0));
	
	// Initialize vectors
	for(i = 1; i < (N+2); i++)	{
		xgrid[i] = (i-1) * h;
		f[i] = func(xgrid[i]);
		df_exact[i] = dfunc(xgrid[i]);	// Analytical solution
		x[i] = 0.0;
	}
	
	// Fill sub, diagonal, super and RHS vectors
	a[1] = 0.0;
	b[1] = 1.0;
	c[1] = 2.0;
	d[1] = (1.0 / h) * (-2.5 * f[1] + 2.0 * f[2] + 0.5 * f[3]);
	for(i = 2; i < (N+1); i++)	{
		a[i] = 1.0;
		b[i] = 4.0;
		c[i] = 1.0;
		d[i] = (3.0 / h) * (f[i+1] - f[i-1]);
	}
	a[N+1] = 2.0;
	b[N+1] = 1.0;
	c[N+1] = 0.0;
	d[N+1] = (1.0 / h) * (2.5 * f[N+1] - 2.0 * f[N] - 0.5 * f[N-1]);
	
	t1 = clock();
	// Elimination phase
	for(k = 1; k <= k_steps; k++)	{
		for(i = 1; i < (N+2); i++)	{
			if (i >= ((int)pow(2, k-1) + 1))	{
				alpha[i] = -a[i] / b[i - (int)pow(2, k-1)];	// Compute alpha[i]
			}
			else        {
				alpha[i] = 0.0;
			}
			
			if (i <= (N + 1 - (int)pow(2, k-1)))	{
				beta[i] = -c[i] / b[i + (int)pow(2, k-1)];	// Compute beta[i]
			}
			else        {
				beta[i] = 0.0;
			}
			
			if (i >= ((int)pow(2, k) + 1))	{
				a[i] = alpha[i] * a[i - (int)pow(2, k-1)];	// Compute a[i]
			}
			else        {
				a[i] = 0.0;
			}
			
			if (i <= (N + 1 - (int)pow(2, k)))	{
				c[i] = beta[i] * c[i + (int)pow(2, k-1)];	// Compute c[i]
			}
			else        {
				c[i] = 0.0;
			}
			
			b[i] = alpha[i] * c[i - (int)pow(2, k-1)] + b[i] + beta[i] * a[i + (int)pow(2, k-1)];	// Compute b[i]
			
			d[i] = alpha[i] * d[i - (int)pow(2, k-1)] + d[i] + beta[i] * d[i + (int)pow(2, k-1)];	// Compute d[i]
		}
	}
	
	// Solution phase
	for(i = 1; i < (N+2); i++)	{
		x[i] = d[i] / b[i];
	}
	t2 = clock();
	comp_time = (double)(t2 - t1) / CLOCKS_PER_SEC;
	
	// Post-processing
	fptr = fopen("serial_recursive_doubling_first_derivative.txt", "w");
	for(i = 1; i < (N+2); i++)	{
		fprintf(fptr, "%lf  %lf  %lf\n", xgrid[i], df_exact[i], x[i]);
	}
	fclose(fptr);	
	
	printf("\n---------- Program ran successfully. Exiting!!! ----------\n");
	printf("Number of divisions, N = %d\n", N);
	printf("Time taken for convergence = %lf\n", comp_time);	
	
	// Deallocate memory
	free(xgrid);
	free(f);
	free(x);
	free(df_exact);
	free(a);
	free(b);
	free(c);
	free(d);
	free(alpha);
	free(beta);
		
	return 0;
}
