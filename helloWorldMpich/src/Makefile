all: helloWorldMpich2.c
	@echo "Making file..."
	mpicc helloWorldMpich2.c -o ../helloWorldMpich2.out -w
	@echo "done"
	@echo "*** sample usage:  mpirun -n 5 ./../helloWorldMpich2.out -machinefile ./src/machinefile ***"

clean:
	@$(RM) ../helloWorldMpich2.out