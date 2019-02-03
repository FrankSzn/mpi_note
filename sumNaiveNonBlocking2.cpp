#include <mpi.h>
#include <vector>

double sumNaiveNonBlocking(double val, int root, MPI_Comm comm)
{
    int rank, size, tag = 42;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);

    double sum = 0;

    if(rank == root){
        std::vector<MPI_Request> requests(size, MPI_REQUEST_NULL);
        std::vector<MPI_Status> statuses(size);
        std::vector<double> others(size, 0.0);
        others[root] = val;

        for(int i = 0; i < size; ++i){
            if (i == root) 
                continue;
            MPI_Irecv(&others[i], 1, MPI_DOUBLE, i, tag, comm, &requests[i]);// Now the non root ranks can return before everyone is done
        
        }
        for(int i = 0; i < size - 1; ++i) {    
        int index;
        MPI_Waitany(requests.size(), requests.data(), &index,  MPI_STATUS_IGNORE );
        sum += others[index];
        }
    }
    else
        MPI_Send(&val, 1, MPI_DOUBLE, root, tag, comm);
    return sum;
}
