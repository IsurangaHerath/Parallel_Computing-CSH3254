#include<mpi.h>
#include<iostream>
int main() {
	int np;
	int pid;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Status sta;



	if (pid == 0) {
		int data[6] = { 1,2,3,4,5,6 };
		int local_sum;
		int local_summ;

		for (int i = 1; i < 6; i++) {
			MPI_Send(&data[i], 1, MPI_INT, i, 50, MPI_COMM_WORLD);
		}
		int my_value = data[0];

		MPI_Recv(&local_sum, 1, MPI_INT, 3, 90, MPI_COMM_WORLD, &sta);
		local_sum = local_sum + my_value;

		MPI_Recv(&local_summ, 1, MPI_INT, 1, 100, MPI_COMM_WORLD, &sta);

		local_summ = local_summ + local_sum;

		printf("Sum is:%d\n", local_summ);
	}

	if (pid == 1) {
		int my_value;
		int local_sum1;
		MPI_Recv(&my_value, 1, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);
		MPI_Recv(&local_sum1, 1, MPI_INT, 2, 60, MPI_COMM_WORLD, &sta);

		local_sum1 = local_sum1 + my_value;

		MPI_Send(&local_sum1, 1, MPI_INT, 0, 100, MPI_COMM_WORLD);
	}

	if (pid == 2) {
		int my_value;
		MPI_Recv(&my_value, 1, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);

		MPI_Send(&my_value, 1, MPI_INT, 1, 60, MPI_COMM_WORLD);
	}

	if (pid == 3) {
		int my_value;
		int local_sum3;
		MPI_Recv(&my_value, 1, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);

		MPI_Recv(&local_sum3, 1, MPI_INT, 4, 80, MPI_COMM_WORLD, &sta);
		local_sum3 = local_sum3 + my_value;

		MPI_Send(&local_sum3, 1, MPI_INT, 0, 90, MPI_COMM_WORLD);

	}

	if (pid == 4) {
		int my_value;
		int local_sum2;
		MPI_Recv(&my_value, 1, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);
		MPI_Recv(&local_sum2, 1, MPI_INT, 5, 70, MPI_COMM_WORLD, &sta);

		local_sum2 = local_sum2 + my_value;
		MPI_Send(&local_sum2, 1, MPI_INT, 3, 80, MPI_COMM_WORLD);

	}

	if (pid == 5) {
		int my_value;
		MPI_Recv(&my_value, 1, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);

		MPI_Send(&my_value, 1, MPI_INT, 4, 70, MPI_COMM_WORLD);
	}

	MPI_Finalize();
	return 0;
}