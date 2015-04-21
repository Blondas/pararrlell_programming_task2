#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct init_params { 
	char * w; 
	int e; 
	int i; 
};

init_params parseInitParameters(int argc, char *const *argv);
void runWorker(init_params);

int main(int argc, char **argv)
{
	//parse init parameters:
	init_params init_params = parseInitParameters(argc, argv);
	
	//run main program:
	runWorker(init_params);
	
	return EXIT_SUCCESS;
}

init_params parseInitParameters(int argc, char *const *argv) {
	init_params init_params;
	init_params.e = 0;
	init_params.i = 0;
	
	int opt; 
	char *optstring = "w:e:i:v";

	char verbose = 0;


	while ((opt = getopt(argc, argv, optstring)) != -1) {
		switch (opt) {
			case 'e':
				init_params.e = atoi(optarg);
				break;

			case 'i':
				init_params.i = atoi(optarg);
				break;
			
			case 'w':
				init_params.w = optarg;
				break;


			case 'v':
				verbose = 1;
				break;

			default:
				printf("cos poszlo nie tak");

				// return EXIT_FAILURE;
				break;
		}
	}

	if (verbose) {
		puts("");
		puts("Printing parameter values:");
		printf("Parameter e = %d\n", init_params.e);
		printf("Parameter i = %d\n", init_params.i);
		printf("Parameter w = %s\n", init_params.w);

		puts("========================");
		puts("");
	}
	
	return init_params;
}

void runWorker(init_params init_params) {
	char command[256];
	snprintf(command, sizeof command, "%s%d%s%d%s%s%s%d%s%d", "mpirun -n 1 -host vnode-01 ./../helloWorldMpich2.out ", 
		init_params.e, " ",init_params.i, " : -n 1 -host ", init_params.w, 
			" ./../helloWorldMpich2.out ", init_params.e, " ",init_params.i);
	
	system(command);
}