#include <mpi.h>
#include <cstdio>

void doWork()
{
    printf("do something\n");
}

void doWorkNeedingSynchronization()
{
    printf("Even ranks wait for odd ranks forever\n");
}

int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    doWork();

    if(rank%2 == 0){
        MPI_Barrier(MPI_COMM_WORLD);// Again, all threads in the communicator MUST call the barrier; otherwise, this creates a deadlock. 
        doWorkNeedingSynchronization();
    }
    MPI_Finalize();
    return 0;
}
