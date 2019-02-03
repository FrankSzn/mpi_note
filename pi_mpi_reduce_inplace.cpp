#include <mpi.h>
#include <algorithm>
#include <cstdio>

int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);

    int size, rank;
    const int tag = 42;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    long nsteps = 100000000;
    double sum = 0;

    long chunk = (nsteps + size - 1) / size;
    long start = chunk * rank;
    long end = std::min(chunk*(rank+1),nsteps);

    for(long i = start; i < end; ++i)
        sum += (1.0 - 2.0*(i %2)) / (2.0 * i + 1.0);

    MPI_Reduce(rank ? &sum : MPI_IN_PLACE, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0)
    {
        printf("pi is around %g\n", sum * 4.0);
    }
    MPI_Finalize();

    return 0;
}
