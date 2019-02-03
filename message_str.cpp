// sending a string with  variable size

#include <mpi.h>
#include <cstdio>
#include <cstring>
int main(int argc, char** argv)
{
    int rank, size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int tag = 42;
    char message[256];

    if (rank == 0){
        for(int i = 1; i < size; ++i){
            sprintf(message, "%d^3 = %d", i, i*i*i);
            MPI_Send(message, strlen(message)+1, MPI_CHAR, i, tag, MPI_COMM_WORLD); 
        }
    }
    else{
        MPI_Status status;
        int count;
        MPI_Recv(message, 256, MPI_CHAR, 0, tag, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_CHAR, &count);
        printf("Rank %d received the following message: '%s'\n"
                "The message contained %d chars\n", rank, message, count);
    }

    MPI_Finalize();
    return 0;
}
