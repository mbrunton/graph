# Makefile for graph_test
# Mitchell Brunton
# June 2013

all: graph_test

graph_test: main.o graph.o priority_queue.o queue.o Makefile
	$(CC) $(CFLAGS) -o graph_test main.o graph.o priority_queue.o queue.o

main.o: graph.h priority_queue.h queue.h Makefile
graph.o: graph.h priority_queue.h queue.h Makefile
priority_queue.o: priority_queue.h Makefile
queue.o: queue.h Makefile

clean:
	/bin/rm *.o graph_test

CC=gcc
CFLAGS=-Wall
