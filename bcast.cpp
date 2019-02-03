// A navie implementation of 
// int MPI_Bcast(void* buffer, int count, MPI_Datatype datatype, int root
// , MPI_Comm comm)
//
#include<mpi.h>

void bcast(void* buffer, int count, MPI_Datatype datatype, int root,MPI_Comm comm)
{
    int rank;
    int size;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);
    
    if(rank == root){
        for(int i = 0; i < size; ++i) {
            if(i == rank) 
                continue;
            MPI_Send(buffer, count, datatype, i, 42, comm);
        }
    }
    else{
        MPI_Recv(buffer, count, datatype, root, 42, comm, MPI_STATUS_IGNORE);
    }
}

// MPI makes use of a tree structure to obtain better performance
