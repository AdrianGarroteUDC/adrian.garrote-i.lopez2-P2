//
// Created by iago on 31/03/25.
//

#include "func_col_mpi.h"

#include <math.h>
#include <mpi.h>

int MPI_FlattreeColectiva(void *buff, void *recvbuff, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm) {
    int numProc, rank, acc, err=MPI_SUCCESS;

    MPI_Comm_size(MPI_COMM_WORLD, &numProc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank != root) {
        err= MPI_Send(buff, count, datatype, root, 0, MPI_COMM_WORLD);
        if (err != MPI_SUCCESS) {
            return err;
        }
    }
    else {
        for (int i = 1; i < numProc; i++) {
            err= MPI_Recv(&acc, count, datatype, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            if (err != MPI_SUCCESS) {
                return err;
            }

            for (int j = 0 ;j < count; j++) {
                ((int*) recvbuff)[j]+= (int*)acc;
            }
        }
    }
    return err;
}

int MPI_BinomialColectiva(void *buff, int count, MPI_Datatype datatype, int root, MPI_Comm comm) {
    int numProc, rank, err = MPI_SUCCESS;

    MPI_Comm_size(comm, &numProc);
    MPI_Comm_rank(comm, &rank);

    int steps = (int)log2(numProc);

    for (int i = 0; i < steps; i++) {
        int partner = rank + pow(2, i);
        if (partner < numProc) {
            if ((rank % (int)pow(2, i+1)) == 0) {
                if (rank == root || (rank % (int)pow(2, i+1)) == 0) {
                    err = MPI_Send(buff, count, datatype, partner, 0, comm);
                    if (err != MPI_SUCCESS) {
                        return err;
                    }
                }
            } else {
                int source = rank - pow(2, i);
                err = MPI_Recv(buff, count, datatype, source, 0, comm, MPI_STATUS_IGNORE);
                if (err != MPI_SUCCESS) {
                    return err;
                }
            }
        }
    }

    return MPI_SUCCESS;
}