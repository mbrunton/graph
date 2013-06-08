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
        exit(EXIT_FAILURE);
    }

    char *filename = argv[1];
    graph_t *G = read_graph(filename);
    print_graph(G);

    search_tree *D = dfs(G);
    print_dfs(D);

    return EXIT_SUCCESS;
}
