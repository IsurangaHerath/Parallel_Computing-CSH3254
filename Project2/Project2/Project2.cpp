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

		int Send_Num[5] = { 10,20,30,40,50 };

		MPI_Send(&Send_Num, 5, MPI_INT, 1, 50, MPI_COMM_WORLD);

		printf("My process id is %d and  i'm the sender.\n", pid);

		int sum = 0;
		for (int i = 0; i < 5; i++) {
			sum = sum + Send_Num[i];
		}

		MPI_Send(&sum, 1, MPI_INT, 1, 60, MPI_COMM_WORLD);
	}

	if (pid == 1) {
		int recv_msg[5];
		int sum = 0;

		MPI_Recv(&recv_msg, 5, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);

		printf("My processor id is %d and i'm the reciever, \n", pid);
		printf("Recieved messages are,");

		for (int i = 0; i < 5; i++) {
			printf("%d\n", recv_msg[i]);
		}

		MPI_Recv(&sum, 1, MPI_INT, 0, 60, MPI_COMM_WORLD, &sta);

		printf("Sum is %d\n", sum);

	}

	MPI_Finalize();
	return 0;
}