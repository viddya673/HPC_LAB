#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
int main(){
	//Declare variables
	int size,rank,info,recv,err0,err1;
	double start,end;
	MPI_Status stat;
	MPI_Request sendreq,recvreq;

	//MPI begins
	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	info = rank;

	//Blocking case begins
	start = MPI_Wtime();
	if(rank==size-1){
		MPI_Recv(&recv,1,MPI_INT,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,&stat);
		MPI_Send(&info,1,MPI_INT,0,0,MPI_COMM_WORLD);
	}else{
		MPI_Send(&info,1,MPI_INT,(rank+1)%size,0,MPI_COMM_WORLD);
		MPI_Recv(&recv,1,MPI_INT,(rank+size-1)%size,0,MPI_COMM_WORLD,&stat);
	}
	MPI_Barrier(MPI_COMM_WORLD);
	end = MPI_Wtime()-start;
	if(rank==0){
		printf("Blocking Comm costs %lf seconds.\n",end);
	}

	//Non-blocking case begins
	start = MPI_Wtime();
	MPI_Isend(&info,1,MPI_INT,(rank+1)%size,     0,MPI_COMM_WORLD,&sendreq);
	MPI_Irecv(&recv,1,MPI_INT,(rank+size-1)%size,0,MPI_COMM_WORLD,&recvreq);
	if(MPI_Wait(&sendreq,&stat)){
		printf("Send failure!\n");
	}
	if(MPI_Wait(&recvreq,&stat)){
		printf("Recv failure!\n");
	}
	MPI_Barrier(MPI_COMM_WORLD);
	end = MPI_Wtime()-start;
	if(rank==0){
		printf("Non-blocking Comm costs %lf seconds.\n",end);
	}

	//Finalize the program
	MPI_Finalize();
}
