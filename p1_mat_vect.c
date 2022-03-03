#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define N 100

int main(){
	int mat[N][N], vect[N], threads, total;
	for(int i=0; i<N; i++)
		for(int j=0; j<N; j++)
			mat[i][j] = rand()%100;
	for(int i=0; i<N; i++)
		vect[i] = rand()%100;
	double start = omp_get_wtime();
#pragma omp parallel for num_threads(4)
	for(int i=0; i<N; i++)
	{
		total = 0;
		for(int j=0; j<N; j++)
#pragma omp critical
		{
			total += mat[i][j] * vect[i];
		}
	threads = omp_get_num_threads();
	}
	printf("total = %d\n", total);
	double end = omp_get_wtime();
	double lapse = end - start;
	printf("threads = %d\n", threads);
	printf("total time lapse = %lf\n", lapse);
}
	
	
			
	
