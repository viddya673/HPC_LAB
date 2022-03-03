#include <stdio.h>
#include <mpi.h>
int main(int argc, char *argv[]){
	int sum=0;
	int rank, size, root=0;
	//MPI_Status stat;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Reduce(&rank, &sum, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);
	if(rank == root)
		printf("SUM= %d\n", sum);
	MPI_Finalize();
}
	
