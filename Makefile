CC = gcc

CFLAGS := -O -Wall

LIBRARY :=

all: test

test: test.c fsm_engine.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBRARY)

clean:
	rm -f test *.o
