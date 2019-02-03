#include <stdio.h>

// pi/ 4 =  \sigma_k(^infinity) (-1)^k / (2*k + 1)

int main(int argc, char** argv)
{
    long nsteps = 100000000;
    double sum = 0;

    for(long i = 0; i < nsteps; ++i)
        sum += (1.0 - 2.0 * ( i % 2)) / (2.0 * i + 1.0);
    printf("pi is around %g\n", sum * 4.0);

    return 0;
}
