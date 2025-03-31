//
// Created by iago on 31/03/25.
//

#ifndef FUNC_COL_MPI_H
#define FUNC_COL_MPI_H
#include <mpi.h>

int MPI_FlattreeColectiva(void *buff, void *recvbuff, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm);

int MPI_BinomialColectiva(void *buff, int count, MPI_Datatype datatype, int root, MPI_Comm comm);


#endif //FUNC_COL_MPI_H
