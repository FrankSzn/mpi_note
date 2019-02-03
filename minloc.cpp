// MPI defines more data types of the form MPI_X_INT
// X = FLOAT, DOUBLE, INT...
// This allows us to use the MPI_MINLOC and MPI_MAXLOC operations

#include <mpi.h>
#include <cstdlib>
#include <cstdio>

int main(int argc, char** argv)
{
    MPI_Init(&argc,&argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    srand48(42 + rank * 42);    // unique seed per rank
    double myval = drand48();

    printf("rank %d has value %g\n", rank, myval);

    struct DoubleInt {
        double val;
        int key;
    } sendBuf = {myval, rank}, recvBuf;
    
    MPI_Reduce(&sendBuf, &recvBuf, 1, MPI_DOUBLE_INT, MPI_MINLOC, 0, MPI_COMM_WORLD);

    if(rank==0)
    {
        printf("The smallest value is %g from rank %d\n", recvBuf.val, recvBuf.key);
    }

    MPI_Finalize();

    return 0;

}
