#include<mpi.h>
#include<stdio.h>
#include<String.h>

int main() {
	int np;
	int pid;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);

	MPI_Status sta;

	if (pid == 0) {

		int send_msg=50;

		for (int i = 1; i <np; i++) {
			MPI_Send(&send_msg, 1, MPI_INT, i, 50, MPI_COMM_WORLD);
			printf("My process id is %d and  i'm the sender to pid %d.\n", pid,i);
		}
	}
	else {
		int recv_msg;

		MPI_Recv(&recv_msg, 1, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);
		printf("My processor id is %d and i'm the reciever.Message is %d\n \n", pid,recv_msg);
	}

	MPI_Finalize();
	return 0;
}