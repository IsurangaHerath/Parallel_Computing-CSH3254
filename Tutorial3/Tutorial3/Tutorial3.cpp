#include<mpi.h>
#include<stdio.h>

int main() {
	int np;
	int pid;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);

	MPI_Status sta;

	if (pid == 0) {
		int seq1[] = { 45,41,92,79,11,83,97,91,98,67,53,34,68,72,76,12,78,59,64,6,89,62,26,23,17,35,36,18,25,55,43,56 };
		int seq2[] = { 5,18,96,63,23,10,42,34,58,84,35,61,51,41,1,13,45,22,53,44,56,96,62,71,67,72,78,46,83,91,97,98 };

		int count = 0;
		int recv_count;

		for (int i = 1; i <4; i++) {
			MPI_Send(&seq1, 32, MPI_INT, i, 50, MPI_COMM_WORLD);
		}

		for (int i = 1; i < 4; i++) {
			MPI_Send(&seq2[(i * 8)], 8, MPI_INT, i, 60, MPI_COMM_WORLD);
		}

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 32; j++) {
				if (seq2[i] == seq1[j]) {
					count = count + 1;
				}
			}
		}

		for (int i = 1; i < 4; i++) {
			MPI_Recv(&recv_count, 1, MPI_INT, i, 70, MPI_COMM_WORLD, &sta);
			count = count + recv_count;
		}
		
		double dc = (2 * count) / double(32 + 32);

		printf("Dice Coefficient is %f\n",dc);
	}

	if (pid == 1) {
		int loc_seq1[32];
		int loc_seq2[8];
		int count = 0;

		MPI_Recv(&loc_seq1, 32, MPI_INT, 0, 50, MPI_COMM_WORLD, & sta);
		MPI_Recv(&loc_seq2, 8, MPI_INT, 0, 60, MPI_COMM_WORLD, &sta);

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 32; j++) {
				if (loc_seq2[i] == loc_seq1[j]) {
					count = count + 1;
				}
			}
		}

		MPI_Send(&count, 1, MPI_INT, 0, 70, MPI_COMM_WORLD);
	}

	if (pid == 2) {
		int loc_seq1[32];
		int loc_seq2[8];
		int count = 0;

		MPI_Recv(&loc_seq1, 32, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);
		MPI_Recv(&loc_seq2, 8, MPI_INT, 0, 60, MPI_COMM_WORLD, &sta);

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 32; j++) {
				if (loc_seq2[i] == loc_seq1[j]) {
					count = count + 1;
				}
			}
		}

		MPI_Send(&count, 1, MPI_INT, 0, 70, MPI_COMM_WORLD);
	}

	if (pid == 3) {
		int loc_seq1[32];
		int loc_seq2[8];
		int count = 0;

		MPI_Recv(&loc_seq1, 32, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);
		MPI_Recv(&loc_seq2, 8, MPI_INT, 0, 60, MPI_COMM_WORLD, &sta);

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 32; j++) {
				if (loc_seq2[i] == loc_seq1[j]) {
					count = count + 1;
				}
			}
		}

		MPI_Send(&count, 1, MPI_INT, 0, 70, MPI_COMM_WORLD);
	}

	MPI_Finalize();
	return 0;
}