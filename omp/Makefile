OMPFLAGS = -fopenmp
OMPLIBS = -lgomp

CC = gcc
CFLAGS = -g -std=gnu99 -I. -Wall $(OMPFLAGS)
LDLIBS = $(OMPLIBS) -lm


MP_SRC1 = gtmp1.c
MP_SRC2 = gtmp2.c

all: mp1 mp2

# The command below compiles the target 'mp1' using the source file 'gtmp1.c' and the object file 'harness.o'.
# The 'harness.o' file is an object file that contains compiled code from the 'harness.c' source file, 
# which likely includes the main function and any necessary setup for the OpenMP program.
mp1: gtmp1.c harness.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

mp2: gtmp2.c harness.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf *.o *.dSYM mp1 mp2
