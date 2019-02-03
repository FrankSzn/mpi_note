#include <mpi.h>

double sumNaive(double val, int root, MPI_Comm comm)
{
    int rank, size, tag = 42;

    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);

    double sum = 0;

    if(rank == root){
        double other;
        sum = val;
        for(int i = 0; i < size; ++i){ 
            if(i == root)
                continue;
            MPI_Recv(&other, 1, MPI_DOUBLE, i, tag, comm, MPI_STATUS_IGNORE); // root can NOT receive a message rank i before receiving the message from rank i-1 because of the blocking receive
            sum += other;
        }
    }
    else
        MPI_Send(&val, 1, MPI_DOUBLE, root, tag, comm);
}
