/* main.c
   program for testing graph.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int
main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s filename\n", argv[0]);
        fprintf(stderr, "filename has format:\nn\nu v w\n...\nu v w\n");
        exit(EXIT_FAILURE);
    }

    char *filename = argv[1];
    graph_t *G = read_graph(filename);

    return EXIT_SUCCESS;
}
