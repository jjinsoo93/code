#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#define NUMSTEPS 1000000

int main(int argc, char *argv[]) {
    int i, rank, size;
    double x, pi, sum = 0.0, local_sum = 0.0;
    double step = 1.0/(double) NUMSTEPS;
    double start_time, end_time, elapsed_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Start the timer (only need one timer for the whole program)
    if (rank == 0) {
        start_time = MPI_Wtime();
    }

    // Divide the work among processes
    for (i = rank; i <= NUMSTEPS; i += size) {
        x = (i + 0.5) * step;
        local_sum += 4.0/(1.0 + x*x);
    }

    // Sum all partial results to calculate pi
    MPI_Reduce(&local_sum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Stop the timer and calculate elapsed time in nanoseconds
    if (rank == 0) {
        end_time = MPI_Wtime();
        elapsed_time = (end_time - start_time) * 1e9;  // Convert to nanoseconds

        pi = step * sum;
        printf("PI is %.20f\n", pi);
        printf("Total elapsed time = %.0f nanoseconds\n", elapsed_time);
    }

    MPI_Finalize();
    return 0;
}
