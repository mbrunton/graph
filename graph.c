/* graph.c
   implements functions described in graph.h
   for performing common algorithms on graphs
*/

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

#define MAX_LINE 80

graph_t *
create_empty_graph(int n) {
    graph_t *G = (graph_t *) malloc(sizeof(graph_t));

    if (NULL == G) {
        fprintf(stderr, "Error, malloc failed\n");
        exit(EXIT_FAILURE);
    }

    G->verts = (vertex_t *) malloc(sizeof(vertex_t) * n);
    int i;
    for (i=0; i<n; i++) {
        G->verts[i].vert_num = i;
        G->verts[i].edgelist = NULL;
    }

    return G;
}

graph_t *
read_graph(char *filename) {
    if (NULL == filename) {
        fprintf(stderr, "Error, bad string passed to read_graph\n");
        exit(EXIT_FAILURE);
    }    

    FILE *fp = fopen(filename, "r");
    int n;
    char *line;

    fgets(line, MAX_LINE, fp);
    sscanf(line, "%d", &n);

    graph_t *G = create_empty_graph(n);
    int u, v, w;
    while (NULL != fgets(line, MAX_LINE, fp)) {
        sscanf(line, "%d %d %d", &u, &v, &w);
        if (u >= n || u < 0 || v >= n || v < 0) {
            fprintf(stderr, "Invalid graph file\n");
            exit(EXIT_FAILURE);
        }
        insert_edge(G, u, v, w);
    }
    
    return G;
}

void
insert_edge(graph_t *G, int u, int v, int w) {
    edge_t *e = G->verts[u].edgelist;
    while (NULL != e) {
        e = e->next;
    }

    e = (edge_t *) malloc(sizeof(edge_t));
    e->u = u;
    e->v = v;
    e->w = w;
    e->next = NULL;
}












