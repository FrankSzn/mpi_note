#include <mpi.h>
#include <cstdio>

void doUsefulWork(){
    printf("doUsefulWork\n");
}

int main(int argc, char** argv){
    double message;
    int rank;
    int tag = 43;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    if(rank == 0){
        message = 11.00;
        MPI_Send(&message, 1, MPI_DOUBLE, 1, tag, MPI_COMM_WORLD);
    }
    else if(rank == 1){
        MPI_Request request;
        MPI_Irecv(&message, 1, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD, &request);
        int messageArrived = 0;

        while(!messageArrived) {
            doUsefulWork();
            MPI_Test(&request, &messageArrived, MPI_STATUS_IGNORE);
        }
        printf("The break is at %g\n", message);
    }
    MPI_Finalize();
    return 0;
}

