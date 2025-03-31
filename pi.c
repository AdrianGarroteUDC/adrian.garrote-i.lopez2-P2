#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
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
    MPI_Reduce(&countLocal, &count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        pi = ((double) count / (double) n) * 4.0;

        printf("pi is approx. %.16f, Error is %.16f\n", pi, fabs(pi - PI25DT));
    }

    MPI_Finalize();
    return 0;
/*
    while (!done)
    {
        printf("Enter the number of points: (0 quits) \n");
        scanf("%d",&n);

        if (n == 0) break;

        count = 0;

        for (i = 1; i <= n; i++) {
            // Get the random numbers between 0 and 1
	    x = ((double) rand()) / ((double) RAND_MAX);
	    y = ((double) rand()) / ((double) RAND_MAX);

	    // Calculate the square root of the squares
	    z = sqrt((x*x)+(y*y));

	    // Check whether z is within the circle
	    if(z <= 1.0)
                count++;
        }
        pi = ((double) count/(double) n)*4.0;

        printf("pi is approx. %.16f, Error is %.16f\n", pi, fabs(pi - PI25DT));
    }
    */
}



