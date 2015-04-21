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

int main(int argc, char **argv)
{
	init_params init_params = parseInitParameters(argc, argv);

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
		puts("Printing parameter values:");
		printf("Parameter e = %d\n", init_params.e);
		printf("Parameter i = %d\n", init_params.i);
		printf("Parameter w = %s", init_params.w);

		puts("");
	}
	
	return init_params;
}
