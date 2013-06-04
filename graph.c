/* graph.c
   implements functions described in graph.h
   for performing common algorithms on graphs
*/

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

#define MAX_LINE 80


graph_t *
read_graph(char *filename) {
    if (NULL == filename) {
        fprintf(stderr, "Error, bad string passed to read_graph\n");
        exit(EXIT_FAILURE);
    }    

    FILE *fp = fopen(filename, "r");
    char *line = (char *) malloc(sizeof(char) * MAX_LINE);

    // get n = order of graph
    int n;
    fgets(line, MAX_LINE, fp);
    sscanf(line, "%d", &n);
    if (n < 1) {
        fprintf(stderr, "Graph must have positive number of vertices\n");
        exit(EXIT_FAILURE);
    }

    // create graph of order n and fill with edges
    graph_t *G = create_empty_graph(n);
    int u, v, w;
    while (NULL != fgets(line, MAX_LINE, fp)) {
        sscanf(line, "%d %d %d", &u, &v, &w);
        if (u >= n || u < 0 || v >= n || v < 0 || u == v) {
            fprintf(stderr, "Invalid edge in graph file\n");
            exit(EXIT_FAILURE);
        }
        insert_edge(G, u, v, w);
    }
    
    return G;
}

graph_t *
create_empty_graph(int n) {
    graph_t *G = (graph_t *) malloc(sizeof(graph_t));

    if (NULL == G) {
        fprintf(stderr, "Error, malloc failed\n");
        exit(EXIT_FAILURE);
    }

    G->n = n;
    G->verts = (vertex_t *) malloc(sizeof(vertex_t) * n);

    int i;
    for (i=0; i<n; i++) {
        G->verts[i].edgelist.head = NULL;
    }

    return G;
}

void
insert_edge(graph_t *G, int u, int v, int w) {
    edge_t *e = G->verts[u].edgelist.head;
    
    if (NULL == e) {
        // first edge off this vertex
        G->verts[u].edgelist.head = (edge_t *) malloc(sizeof(edge_t));
        G->verts[u].edgelist.head->u = u;
        G->verts[u].edgelist.head->v = v; 
        G->verts[u].edgelist.head->w = w;
        G->verts[u].edgelist.head->next = NULL;
        return;
    }

    while (NULL != e->next) {
        if (e->u == u && e->v == v) {
            // edge already exists
            e->w = w;
            return;
        }
        e = e->next;
    }
    e->next = (edge_t *) malloc(sizeof(edge_t));
    e->next->u = u;
    e->next->v = v;
    e->next->w = w;
    e->next->next = NULL;
}

void
print_graph(graph_t *G) {
    int i;
    edge_t *e;
    fprintf(stderr, "G->n = %d\n\n", G->n);

    for (i = 0; i < G->n; i++) {
        fprintf(stderr, "%d:  ", i);
        e = G->verts[i].edgelist.head;

        while (NULL != e) {
            fprintf(stderr, "--(%d)--> %d,      ", e->w, e->v);
            e = e->next;
        }
        fprintf(stderr, "\n");
    }
}










