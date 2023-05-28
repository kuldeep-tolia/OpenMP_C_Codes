#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#ifdef _OPENMP
#include <omp.h>
#endif

#define N1 10
#define N2 50

void oddEvenSort(int *vec, int n)	{
	
	int i, pass;
	int thread_count = omp_get_num_threads();
	
	#pragma omp parallel num_threads(thread_count) default(none) shared(vec, n) private(i, pass)
	{
		for(pass = 0; pass < n; pass++)	{
			if(pass % 2 == 0)	{
				#pragma omp for
				for(i = 1; i < n; i=i+2)	{
					if(vec[i-1] > vec[i])	{
						vec[i] = vec[i] + vec[i-1];
						vec[i-1] = vec[i] - vec[i-1];
						vec[i] = vec[i] - vec[i-1];
					}
				}
			}
			else    {
				#pragma omp for
				for(i = 1; i < n-1; i=i+2)	{
					if(vec[i] > vec[i+1])	{
						vec[i] = vec[i] + vec[i+1];
						vec[i+1] = vec[i] - vec[i+1];
						vec[i] = vec[i] - vec[i+1];
					}
				}
			}
		}
	}
			
	return;
}

void displayVector(int *vec, int n)	{
	for(int i = 0; i < n; i++)	{
		printf("%d\t", vec[i]);
	}
	printf("\n");
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
	
	int *vec1 = (int *)malloc(N1 * sizeof(int));
	int *vec2 = (int *)malloc(N2 * sizeof(int));
	int i;
	
	srand(time(NULL));
	for(i = 0; i < N1; i++)	{
		vec1[i] = rand() % 100;
	}
	
	for(i = 0; i < N2; i++)	{
		vec2[i] = rand() % 100;
	}
	
	printf("-----Unsorted vector-1-----\n");
	displayVector(vec1, N1);
	oddEvenSort(vec1, N1);
	printf("\n-----Sorted vector-1-----\n");
	displayVector(vec1, N1);
	
	printf("\n\n-----Unsorted vector-2-----\n");
	displayVector(vec2, N2);
	oddEvenSort(vec2, N2);
	printf("\n-----Sorted vector-2-----\n");
	displayVector(vec2, N2);
	
	free(vec1);
	free(vec2);
		
	return 0;
}
