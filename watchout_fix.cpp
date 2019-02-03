#include <mpi.h>
#include <cstdio>

int main(int argc, char** argv)
{
    int rank, size;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int tag = 42;
    MPI_Request sendReqs[2];
    MPI_Status statuses[2];

    if (rank == 0){
        int message = 7;

        // Add duplicate memory buffer here
        int message_duplicate = 14;
        MPI_Isend(&message, 1, MPI_INT, 1, tag, MPI_COMM_WORLD, &sendReqs[0]);
        //message = 14;// Send is not necessarily completed, can not reuse thebuffer! The first send might 14 instead of 7.
        //Possible fixes:
        // * duplicate the memory buffer
        // * MPI_Wait after first send
        MPI_Isend(&message_duplicate, 1, MPI_INT, 1, tag, MPI_COMM_WORLD, &sendReqs[1]);
        int a = MPI_Waitall(2, sendReqs, statuses);
        printf("MPI_Waitall return code is %d\n", a);
    }
    else if (rank == 1)
    {
        int r1, r2;
        MPI_Recv(&r1, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&r2, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Rank %d received the following integer: %d %d\n", rank, r1, r2);
    }
    MPI_Finalize();
    return 0;
}
