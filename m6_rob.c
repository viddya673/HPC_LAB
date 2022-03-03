#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#define N 100
int main(int argc, char *argv[])
{
  
  int rank, size, break_point, prob[N],value[N],from,to,num=0;
  for (int i = 0; i < N; ++i)
  {
    /* code */
    num = rand() % 2;
    prob[i]=num;
  }
  
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  MPI_Scatter(prob, N/size,MPI_INT,value,N/size,MPI_INT,0,MPI_COMM_WORLD);

  int failure,sum;
  
  for(int i=0; i<N/size;i++)
  {
    if(value[i]==1)
      failure++;
  }
  printf("process %d has picked %d mangoes\n", rank, failure);

  MPI_Reduce(&failure,&break_point,1,MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  if(rank == 0)
  {
    printf("Maximum mangoes picked: (%d)\nTerminating process.\n", break_point);
    MPI_Finalize();
  }
  else{
    MPI_Finalize();
  }

  return 0;
}
