# Makefile for graph_test

all: graph_test

graph_test: main.o graph.o Makefile
	$(CC) $(CFLAGS) -o graph_test main.o graph.o

main.o: graph.h Makefile
graph.o: graph.h Makefile

clean:
	/bin/rm *.o graph_test

CC=gcc
CFLAGS=-Wall
