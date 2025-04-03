//
// Created by iago on 31/03/25.
//

#include "func_col_mpi.h"
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int MPI_FlattreeColectiva(void *buff, void *recvbuff, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm) {
    int numProc, rank, err=MPI_SUCCESS;
    int *acc;

    MPI_Comm_size(MPI_COMM_WORLD, &numProc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank != root) {
        err= MPI_Send(buff, count, datatype, root, 0, MPI_COMM_WORLD);
        if (err != MPI_SUCCESS) {
            return err;
        }
    }
    else {
        for (int j = 0 ;j < count; j++) {
            ((int*) recvbuff)[j]= ((int*)buff)[j];
        }
        acc= (int*) malloc(count*sizeof(int));
        for (int i = 1; i < numProc; i++) {

            err= MPI_Recv(acc, count, datatype, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            if (err != MPI_SUCCESS) {
                return err;
            }
            for (int j = 0 ;j < count; j++) {
                ((int*) recvbuff)[j]+= acc[j];
            }


        }
        free(acc);
    }
    return err;
}

int MPI_BinomialColectiva(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm) {
    int num_procs, rank, err = MPI_SUCCESS;

    MPI_Comm_size(comm, &num_procs);
    MPI_Comm_rank(comm, &rank);

    // Pasos hasta sol
    int pNecesarios = 0;
    int potenciaDos = 1;
    while (potenciaDos < num_procs) {
        potenciaDos *= 2;
        pNecesarios++;
    }

    // Fase de difusión
    potenciaDos = 1;  // Reset
    for (int i = 0; i < pNecesarios; i++) {
        int distancia = potenciaDos;  // 2^i

        if (rank < distancia) {
            int procReceptor = rank + distancia;
            if (procReceptor < num_procs) {
                printf("Proceso %d enviando a proceso %d\n", rank, procReceptor);
                err = MPI_Send(buffer, count, datatype, procReceptor, 0, comm);
                if (err != MPI_SUCCESS) return err;
            }
        }
        else if (rank < 2 * distancia) {
            int procEnvia = rank - distancia;
            err = MPI_Recv(buffer, count, datatype, procEnvia, 0, comm, MPI_STATUS_IGNORE);
            if (err != MPI_SUCCESS) return err;
            printf("Proceso %d recibió datos de proceso %d\n", rank, procEnvia);
        }

        potenciaDos *= 2;
    }

    return MPI_SUCCESS;
}