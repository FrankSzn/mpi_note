#include <mpi.h>
#include<cstdio>

int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);
    printf("Hello HPCSE class!\n");
    MPI_Finalize();
    return 0;
}
