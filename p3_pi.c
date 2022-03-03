#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
static long num_steps;
double step;
int main(){
	int i;
	double x, pi, sum=0.0;
	printf("Enter number of steps:\t");
	scanf("%ld", &num_steps);
	if(num_steps <= 0){
		printf("positive integer required\n");
		exit(1);
	}
	step = 1.0/num_steps;
	double start = omp_get_wtime();
#pragma omp parallel for private(x) reduction(+:sum)
	for(i=1; i<=num_steps; i++){
		x = (i-0.5)*step;
		sum += 4.0/(1.0 + x*x);
	}
	double end = omp_get_wtime() - start;
	pi = sum/num_steps;
	printf("pi = %lf\n", pi);
	printf("Total time = %lf\n", end);
}
	
