#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main() {
    int np;
    int pid;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);

    MPI_Status sta;

    if (pid == 0) {

        int recv_msg;

        for (int i = 1; i < np; i++) {
            MPI_Recv(&recv_msg, 1, MPI_INT, i, 50, MPI_COMM_WORLD, &sta);
            printf("Process 0 received %d from process %d\n", recv_msg, i);
        }
    }
    else {
        int send_msg = pid * 10;
        MPI_Send(&send_msg, 1, MPI_INT, 0, 50, MPI_COMM_WORLD);
        printf("Process %d sent message %d to process 0\n", pid, send_msg);
    }

    MPI_Finalize();
    return 0;
}
/*

#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main() {
    int np;
    int pid;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);

    MPI_Status sta;

    if (pid == 0) {
        int recv_msg;
        int recv_array[50]; 

        for (int i = 1; i < np; i++) {
            MPI_Recv(&recv_msg, 1, MPI_INT, i, 50, MPI_COMM_WORLD, &sta);
            recv_array[i] = recv_msg; 
            printf("Process 0 received %d from process %d\n", recv_msg, i);
        }

        printf("\nStored values in array:\n");
        for (int i = 1; i < np; i++) {
            printf("recv_array[%d] = %d\n", i, recv_array[i]);
        }
    }
    else {
        int send_msg = pid * 10;
        MPI_Send(&send_msg, 1, MPI_INT, 0, 50, MPI_COMM_WORLD);
        printf("Process %d sent message %d to process 0\n", pid, send_msg);
    }

    MPI_Finalize();
    return 0;
}
*/