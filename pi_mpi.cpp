#include <cstdio>
#include <mpi.h>
#include <algorithm>


// pi/ 4 =  \sigma_k(^infinity) (-1)^k / (2*k + 1)

int main(int argc, char** argv)
{
    MPI_Init(&argc,&argv);
    int size, rank;
    const int tag = 42;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    long nsteps = 100000000;
    double sum = 0;
    
    long chunk = (nsteps + size - 1) / size;
    long start = chunk * rank;
    long end = std::min(chunk * (rank+1), nsteps);



    for(long i = start; i < end; ++i)
        sum += (1.0 - 2.0 * ( i % 2)) / (2.0 * i + 1.0);
    
    if (rank == 0){
        double tot_sum = sum;
        double other;
        for(int i = 1; i < size; ++i){
            MPI_Recv(&other, 1, MPI_DOUBLE, i, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            tot_sum += other;
        }
        printf("pi is around %g\n", tot_sum * 4.0);
    }
    else{
        MPI_Ssend(&sum, 1, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}
