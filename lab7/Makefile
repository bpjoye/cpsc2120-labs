CC = g++
DEBUG = -g
CFLAGS = -Wall -std=gnu++11 $(DEBUG)
LFLAGS = -Wall $(DEBUG)

compile: lab07.out

lab07.out: lab07.cpp memoization.h integration.h
	$(CC) $(CFLAGS) -o lab07.out lab07.cpp

run: lab07.out
	./lab07.out

clean:
	rm *.out