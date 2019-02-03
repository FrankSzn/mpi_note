#include <mpi.h>
#include <cstdio>

int main(int argc, char** argv)
{
    int rank, size, bufsize;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int tag1 = 42, tag2 = 43;

    int sendMessage, recvMessage;
    
    MPI_Pack_size(1, MPI_INT, MPI_COMM_WORLD, &bufsize);
    bufsize += MPI_BSEND_OVERHEAD;
    printf("bufsize is %d, MPI_BSEND_OVERHEAD is %d\n", bufsize, MPI_BSEND_OVERHEAD);
    char *buffer = new char[bufsize];
    MPI_Buffer_attach(buffer,bufsize);
    if(rank == 0){
        sendMessage = 7;
        MPI_Bsend(&sendMessage, 1, MPI_INT, 1, tag1, MPI_COMM_WORLD);
        MPI_Recv(&recvMessage, 1, MPI_INT, 1, tag2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }else if (rank == 1){
        sendMessage = 14; 
        MPI_Bsend(&sendMessage, 1, MPI_INT, 0, tag2, MPI_COMM_WORLD);
        MPI_Recv(&recvMessage, 1, MPI_INT, 0, tag1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    printf("Rank %d received the following integer: %d\n", rank, recvMessage);
    MPI_Buffer_detach(buffer, &bufsize);
    delete[] buffer;
    MPI_Finalize();
    return 0;
}
