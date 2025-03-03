MPICC = mpicc.mpich

OMPFLAGS = -fopenmp
OMPLIBS = -lgomp

CFLAGS = -g -std=gnu99 -I. -Wall $(OMPFLAGS)
LDLIBS = $(OMPLIBS) -lm

all: combined 

harness.o: harness.c
	$(MPICC) -c $(CFLAGS) $< -o $@

combined: gtcombined.c harness.o
	$(MPICC) $(CFLAGS) -o $@ gtcombined.c ../omp/gtmp2.c ../mpi/gtmpi1.c harness.o $(LDLIBS)

clean:
	rm -rf *.o *.dSYM combined