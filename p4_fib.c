#include<stdio.h>
#include<omp.h>

void main(){
	int n, a[100], i;
	printf("Enter the no. of items to generate fibonacci series:\n");
	scanf("%d", &n);
	a[0] = 0;
	a[1] = 1;
	double start = omp_get_wtime();
#pragma omp parallel num_threads(2) 
{
#pragma omp single
	for(i=2; i<n; i++)
		a[i] = a[i-2] + a[i-1];
#pragma omp barrier
#pragma omp single
	for(i=0; i<n; i++)
		printf("%d\n", a[i]);
}
	double end = omp_get_wtime() - start;
	printf("Total time = %lf", end);
}	
		
	
	
	
