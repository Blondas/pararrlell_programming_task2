all: wrapper.c
	@echo "Making files..."
	@g++ wrapper.c -o ../wrapper.out -w
	@mpicc helloWorldMpich2.c -o ../helloWorldMpich2.out -w
	@echo "done"
	@echo "*** sample usage:  ./../wrapper.out -w vnode-02 -e 25 -i 10 -v ***"

clean:
	@$(RM) ../wrapper.out
	@$(RM) ../helloWorldMpich2.out