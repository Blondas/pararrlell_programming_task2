#include <stdlib.h>
#include <stdio.h>

#include <mpi.h>

void master() {
	int size;
	MPI_Status status;

	char processor_name[MPI_MAX_PROCESSOR_NAME + 1];
	int processor_name_length;

	int i;

	// Pobieramy iloœæ wszystkich wêz³ów, które
	// bior¹ udzia³ w obliczeniach
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	// Pobieramy nazwê procesora pamiêtaj¹c o ograniczeniu
	// ci¹gu znaków przez znak '\0'
	MPI_Get_processor_name(processor_name, &processor_name_length);
	processor_name[processor_name_length] = '\0';

	printf("\nI'm the master process (rank 0) on node: %s\n", processor_name);
	printf("I've received the following messages:\n");
	puts("");

	// Odbieramy wiadomoœci przes³ane przez workerów.
	// Jako "workerów" traktujemy wêz³y o rankach
	// (identyfikatorach) pomiêdzy 1 a "(size - 1)".
	// Procesy numerowane s¹ od 0 a¿ do "(size - 1)".
	for (i = 1; i < size; i++) {
		MPI_Recv((void*) processor_name,
			MPI_MAX_PROCESSOR_NAME + 1,
			MPI_CHAR,
			i,
			MPI_ANY_TAG,
			MPI_COMM_WORLD,
			&status);

		printf("Msg received from rank %d: %s\n", i, processor_name);
	}

	puts("");
}

void worker() {
	char processor_name[MPI_MAX_PROCESSOR_NAME + 1];
	int processor_name_length;

	// Pobieramy nazwê procesora (wêz³a), na którym uruchomiony
	// jest worker
	MPI_Get_processor_name(processor_name, &processor_name_length);
	processor_name[processor_name_length] = '\0';

	// Przesy³amy pobran¹ nazwê do procesu "master" (o ranku 0)
	MPI_Send((void*) processor_name,
		processor_name_length + 1,
		MPI_CHAR,
		0,
		0,
		MPI_COMM_WORLD);
}

int main(int argc, char **argv) {
	int rank, returned_rank;
	double t1, t2;

	
	
	MPI_Init(&argc, &argv);
	t1 = MPI_Wtime();
	
	sleep(1);
	

	returned_rank = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	printf("rank = %d, returned_rank = %d\n", rank, returned_rank);
	
	if (!rank) {
		master();
	} else {
		worker();
	}

	
	t2 = MPI_Wtime();
	MPI_Finalize();
	
	
	printf("MPI_Wtime measured a 1 second sleep to be : %1.2f\n", t2 - t1) ;

	exit(EXIT_SUCCESS);
}