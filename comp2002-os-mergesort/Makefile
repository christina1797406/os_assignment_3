CC = gcc
CFLAGS = -Wall -Wpointer-arith -Wstrict-prototypes -std=c11 -fPIC -MMD -MP -lpthread

all: test-mergesort

#This builds an executable 
test-mergesort: test-mergesort.o mergesort.o
	$(CC) $(CFLAGS) -o $@ $?

.PHONY: clean
clean:
	/bin/rm -f *.o *.d test-mergesort
