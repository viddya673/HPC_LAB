#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<omp.h>
#define MAX 3694726
void main(){
	float *arr, cur_max;
	int i, n;
	srand(MAX);
	printf("Enter the number of elements:\t");
	scanf("%d", &n);
	arr = (float*)malloc(sizeof(float)*n);
	for(i=0; i<n; i++){
		arr[i] = (float)rand()/(float)(RAND_MAX)*10;
		printf("%f\t", arr[i]);
	}
	if(n==1){
		printf("max cgpa = %f\n", arr[0]);
		exit(1);
	}
	cur_max = arr[0];
	double start = omp_get_wtime();
#pragma omp parallel for
	for(i=1; i<n; i++){
#pragma omp critical
		if(cur_max < arr[i])
			cur_max = arr[i];
	}
	double end = omp_get_wtime() - start;
	printf("max cgpa = %f\n", cur_max);
	printf("total time = %lf\n", end);
}		
