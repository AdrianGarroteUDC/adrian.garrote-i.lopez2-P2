#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"
#include "func_col_mpi.h"

int main(int argc, char *argv[]) {
    int i, done = 0, rank, numProc, count, n;
    double PI25DT = 3.141592653589793238462643;
    double pi, x, y, z;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numProc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        printf("Enter the number of points: (0 quits) \n");
        scanf("%d", &n);
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Reparto del Trabajo
    int countLocal = 0;
    for (i = rank; i < n; i += numProc) {
        x = ((double) rand()) / ((double) RAND_MAX);
        y = ((double) rand()) / ((double) RAND_MAX);
        z = sqrt((x * x) + (y * y));

        if (z <= 1.0) countLocal++;
    }

    // Final
    //count = countLocal;
    MPI_(&countLocal, &count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        pi = ((double) count / (double) n) * 4.0;

        printf("pi is approx. %.16f, Error is %.16f\n", pi, fabs(pi - PI25DT));
    }

    MPI_Finalize();
    return 0;
}



