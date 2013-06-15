/* main.c
   program for testing graph.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "priority_queue.h"

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

    pq_t *Q = create_empty_pq(5);
    int i;
    for (i = 0; i < 5; i++) {
        push(Q, (void *) NULL, 100 - i);
        print_pq(Q);
    }
    for (i = 0; i < 5; i++) {
        pop(Q);
        print_pq(Q);
    }

    return EXIT_SUCCESS;
}


