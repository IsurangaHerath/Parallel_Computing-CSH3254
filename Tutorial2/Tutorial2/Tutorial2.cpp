#include <mpi.h>
#include <stdio.h>

int main() {
    int np, pid;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);

    int msg;
    MPI_Status status;

    if (pid == 0) {
        msg = 100; 
        printf("Process 0 starts with %d\n", msg);

        MPI_Send(&msg, 1, MPI_INT, (pid + 1) % np, 0, MPI_COMM_WORLD);

        MPI_Recv(&msg, 1, MPI_INT, np - 1, 0, MPI_COMM_WORLD, &status);
        printf("Process 0 received final value %d from process %d\n", msg, np - 1);
    }
    else {
        MPI_Recv(&msg, 1, MPI_INT, pid - 1, 0, MPI_COMM_WORLD, &status);
        printf("Process %d received %d from process %d\n", pid, msg, pid - 1);

        MPI_Send(&msg, 1, MPI_INT, (pid + 1) % np, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
