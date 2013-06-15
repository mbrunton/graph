# Makefile for graph_test
# Mitchell Brunton
# June 2013

all: graph_test

graph_test: main.o graph.o priority_queue.o Makefile
	$(CC) $(CFLAGS) -o graph_test main.o graph.o priority_queue.o

main.o: graph.h priority_queue.h Makefile
graph.o: graph.h Makefile
priority_queue.o: priority_queue.h Makefile

clean:
	/bin/rm *.o graph_test

CC=gcc
CFLAGS=-Wall
