#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#ifdef _OPENMP
#include <omp.h>
#endif

#define N 3000

void printMatrix(int m, double **matrix)	{
	for(int i = 0; i < m; i++)	{
		for(int j = 0; j < m; j++)	{
			printf("%lf ", matrix[i][j]);
		}
		printf("\n");
	}
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
	
	// Allocate matrices
	double **mat1 = (double **)malloc(N * sizeof(double *));
	double **mat2 = (double **)malloc(N * sizeof(double *));
	double **mat3 = (double **)malloc(N * sizeof(double *));
	
	double t1, t2;
	int i, j, k;
	
	for(j = 0; j < N; j++)	{
		mat1[j] = (double *)malloc(N * sizeof(double));
		mat2[j] = (double *)malloc(N * sizeof(double));
		mat3[j] = (double *)malloc(N * sizeof(double));
	}
	
	// Initialize matrices
	#pragma omp parallel for collapse(2) num_threads(num_thread) default(shared) private(i, j)
	for(i = 0; i < N; i++)	{
		for(j = 0; j < N; j++)	{
			mat1[i][j] = 1.0;
			mat2[i][j] = 1.0;
			mat3[i][j] = 0.0;
		}
	}
		
	t1 = omp_get_wtime();
	#pragma omp parallel for collapse(2) num_threads(num_thread) default(shared) private(i, j, k)
	for(i = 0; i < N; i+=2)	{
		for(j = 0; j < N; j+=2)	{	// Loop unrolling along with row access
			mat3[i][j] = 0.0;
			mat3[i+1][j] = 0.0;
			mat3[i][j+1] = 0.0;
			mat3[i+1][j+1] = 0.0;
			for(k = 0; k < N; k++)	{
				mat3[i][j] = mat3[i][j] + mat1[i][k] * mat2[j][k];
				mat3[i+1][j] = mat3[i+1][j] + mat1[i+1][k] * mat2[j][k];
				mat3[i][j+1] = mat3[i][j+1] + mat1[i][k] * mat2[j+1][k];
				mat3[i+1][j+1] = mat3[i+1][j+1] + mat1[i+1][k] * mat2[j+1][k];
			}
		}
	}
	t2 = omp_get_wtime();
	
	printf("Number of threads = %d, N = %d\n", num_thread, N);
	printf("Execution time = %lf seconds\n", t2-t1);
	printf("Sanity check ----> printing random index of the product matrix = %lf\n", mat3[N/2][N/2]);
	
/*	// Print matrices
	printf("\nProduct of two matrices:\n");
	printMatrix(N, mat3);	*/
	
	// Deallocate matrices
	for(i = 0; i < N; i++)	{
		free(mat1[i]);
		free(mat2[i]);
		free(mat3[i]);
	}
	
	free(mat1);
	free(mat2);
	free(mat3);		
	return 0;
}
