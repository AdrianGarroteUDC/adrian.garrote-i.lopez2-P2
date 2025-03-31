//
// Created by iago on 31/03/25.
//

#include "func_col_mpi.h"
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
            err= MPI_Recv(&acc, 1, datatype, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

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
    int numProc, rank, acc, err=MPI_SUCCESS;

    MPI_Comm_size(MPI_COMM_WORLD, &numProc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


}
