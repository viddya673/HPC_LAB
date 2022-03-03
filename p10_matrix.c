#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define N 100

int A[N][N];
int B[N][N];
int C[N][N];
int D[N][N];

int main() 
{
    int i,j,k;
    omp_set_num_threads(omp_get_num_procs());
    for (i= 0; i< N; i++)
        for (j= 0; j< N; j++)
	{
            A[i][j] = rand() % 100 + 1;
            B[i][j] = rand() % 100 + 1;
	}
    double start = omp_get_wtime();
    #pragma omp parallel for private(i,j,k) shared(A,B,C)
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            for (k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    double end = omp_get_wtime(); 
    //for (i= 0; i< N; i++){
      //  for (j= 0; j< N; j++)
	//{
          //  printf("%d\t",C[i][j]);   
	//}
	//printf("\n");  
    //}
 
    double start2 = omp_get_wtime();
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            for (k = 0; k < N; ++k) {
                D[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    double end2 = omp_get_wtime();
    double elapsed = end - start;
    double elapsed2 = end2 - start2;
    printf("elapsed time for parallel = %f seconds.\n", elapsed);
    printf("elapsed time for serial = %f seconds.\n", elapsed2);
    }
