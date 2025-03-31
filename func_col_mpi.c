//
// Created by iago on 31/03/25.
//

#include "func_col_mpi.h"
#include <mpi.h>

int MPI_FlattreeColectiva(void *buff, void *recvbuff, int count, MPI_Datatype datatype, int root, MPI_Comm comm) {
    int numProc, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &numProc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
}

int MPI_BinomialColectiva(void *buff, int count, MPI_Datatype datatype, int root, MPI_Comm comm);
