#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    // Initialize MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank (ID) of each process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // Print information about this process
    printf("Hello from processor %s, rank %d out of %d processors\n",
           processor_name, world_rank, world_size);

    // Begin parallel work - put your parallel task code here
    // *******************************************************
    // This is where you need to place the code to be run in parallel by each thread.
    // Each process will execute this block independently.
    // Example: Have each process print its rank multiplied by some number
    int work_result = world_rank * 10;
    printf("Process %d did some work: result = %d\n", world_rank, work_result);
    // *******************************************************

    // Finalize the MPI environment
    MPI_Finalize();

    return 0;
}