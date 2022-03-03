/*A simplified mapping of processes into a Cartesian virtual topology appears below:
 _______________________________
|   0   |   1   |   2   |   3   |
| (0,0) | (0,1) | (0,2) | (0,3) |
|_______|_______|_______|_______|
|   4   |   5   |   6   |   7   |
| (1,1) | (1,2) | (1,3) | (1,4) |
|_______|_______|_______|_______|
|   8   |   9   |  10   |  11   |
| (2,1) | (2,2) | (2,3) | (2,4) |
|_______|_______|_______|_______|
|   12  |   13  |   14  |   15  |
| (3,1) | (3,2) | (3,3) | (3.4) |
|_______|_______|_______|_______|*/
#include <mpi.h>
#include <stdio.h>
#define SIZE 16
#define UP    0
#define DOWN  1
#define LEFT  2
#define RIGHT 3

int main(int argc, char *argv[])  {
int numtasks, rank, source, dest, outbuf, i,
    nbrs[4], dims[2]={4,4},
    periods[2]={0,0}, reorder=0, coords[2];

MPI_Comm cartcomm;   // required variable

MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

if (numtasks == SIZE) {
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, reorder, &cartcomm);
    MPI_Comm_rank(cartcomm, &rank);
    MPI_Cart_coords(cartcomm, rank, 2, coords);
    MPI_Cart_shift(cartcomm, 0, 1, &nbrs[UP], &nbrs[DOWN]);
    MPI_Cart_shift(cartcomm, 1, 1, &nbrs[LEFT], &nbrs[RIGHT]);

    printf("rank= %d coords= %d %d  neighbors(u,d,l,r)= %d %d %d %d\n",
            rank,coords[0],coords[1],nbrs[UP],nbrs[DOWN],nbrs[LEFT],
            nbrs[RIGHT]);
     }
else
    printf("Must specify %d processors. Terminating.\n",SIZE);

MPI_Finalize();
return 0;
}

