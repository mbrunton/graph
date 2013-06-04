/* graph.c
   implements functions described in graph.h
   for performing common algorithms on graphs
*/

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


// AUXILIARY FUNCTIONS
void insert_edge(graph_t *G, int u, int v, int w);
dfs_struct *create_empty_dfs_struct(int n);
void explore(graph_t *G, dfs_struct *D, int u);

/* input file must have format:

n directed
u v w
...
u v w
(EOF)
    
    where: 
    n is a positive integer (order of graph),
    directed is either 0 or 1
    u, v are integers denoting adjacent vertices
    all u, v obey 0 <= u,v < n, and u != v
    w are integers (weights of edges)
   
*/
graph_t *
read_graph(char *filename) {
    if (NULL == filename) {
        fprintf(stderr, "Error, bad string passed to read_graph\n");
        exit(EXIT_FAILURE);
    }    

    FILE *fp = fopen(filename, "r");
    char *line = (char *) malloc(sizeof(char) * MAX_LINE);

    // get n = order of graph, and whether graph is directed
    int n;
    int directed;
    fgets(line, MAX_LINE, fp);
    sscanf(line, "%d %d", &n, &directed);
    if (n < 1) {
        fprintf(stderr, "Error: Graph must have positive number of vertices\n");
        exit(EXIT_FAILURE);
    }
    if (directed != 1 && directed != 0) {
        fprintf(stderr, "Error: directed must be set to 1 or 0\n");
        exit(EXIT_FAILURE);
    }


    // create graph of order n and fill with edges
    graph_t *G = create_empty_graph(n, directed);

    int u, v, w;
    while (NULL != fgets(line, MAX_LINE, fp)) {
        sscanf(line, "%d %d %d", &u, &v, &w);
        if (u >= n || u < 0 || v >= n || v < 0 || u == v) {
            fprintf(stderr, "Invalid edge in graph file\n");
            exit(EXIT_FAILURE);
        }

        insert_edge(G, u, v, w);
        if (!G->directed) {
            insert_edge(G, v, u, w);
        }
    }
    
    return G;
}

graph_t *
create_empty_graph(int n, int directed) {
    graph_t *G = (graph_t *) malloc(sizeof(graph_t));

    if (NULL == G) {
        fprintf(stderr, "Error, malloc failed\n");
        exit(EXIT_FAILURE);
    }

    G->n = n;
    G->directed = directed;
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
        e = e->next;
    }
    e->next = (edge_t *) malloc(sizeof(edge_t));
    e->next->u = u;
    e->next->v = v;
    e->next->w = w;
    e->next->next = NULL;

    return;
}


// returns graph of dfs tree
dfs_struct *
dfs(graph_t *G) {
    dfs_struct *D = create_empty_dfs_struct(G->n);

    int i;
    for (i = 0; i < G->n; i++) {
        if (D->dfi_array[i] == UNDEFINED) {
            explore(G, D, i);
            D->k++;
        }
    }

    return D;
}

void
explore(graph_t *G, dfs_struct *D, int u) {
    // mark vertex u as visited
    D->dfi_array[u] = D->dfi_counter;
    D->dfi_counter++;

    // explore u's neighbors
    int v;
    edge_t *e = G->verts[u].edgelist.head;
    while (NULL != e) {
        v = e->v;
        if (D->dfi_array[v] == UNDEFINED) {
            // add edge e to our forest and start exploring v
            insert_edge(D->T, e->u, e->v, e->w);
            D->parents[v] = u;
            explore(G, D, v);
        }
        e = e->next;
    }
    return;
}

dfs_struct *
create_empty_dfs_struct(int n) {
    dfs_struct *D = (dfs_struct *) malloc(sizeof(dfs_struct));

    D->T = create_empty_graph(n, FALSE);
    D->parents = (int *) malloc(sizeof(int) * n);
    D->dfi_array = (int *) malloc(sizeof(int) * n);
    D->dfi_counter = 0;
    D->k = 0;

    int i;
    for (i = 0; i < n; i++) {
        D->parents[i] = UNDEFINED;
        D->dfi_array[i] = UNDEFINED;
    }
    return D;
}

void
print_graph(graph_t *G) {
    int i;
    edge_t *e;
    fprintf(stderr, "GRAPH PRINTOUT:\n");
    fprintf(stderr, "n = %d\n", G->n);
    for (i = 0; i < G->n; i++) {
        fprintf(stderr, "%d:  ", i);

        e = G->verts[i].edgelist.head;
        while (NULL != e) {
            fprintf(stderr, "--(%d)--> %d,      ", e->w, e->v);
            e = e->next;
        }
        fprintf(stderr, "\n");
    }
    fprintf(stderr, "\n");
    return;
}

void
print_dfs(dfs_struct *D) {
    int i;
    edge_t *e;
    fprintf(stderr, "DEPTH-FIRST SEARCH PRINTOUT:\n");
    fprintf(stderr, "k = %d\n", D->k);

    for (i = 0; i < D->T->n; i++) {
        fprintf(stderr, "%d: ", i);

        if (D->parents[i] == UNDEFINED) {
            fprintf(stderr, "(root), ");
        } else {
            fprintf(stderr, "parent = %d, ", D->parents[i]);
        }
        fprintf(stderr, "dfi = %d\n", D->dfi_array[i]);
    }
    fprintf(stderr, "\n");

    for (i = 0; i < D->T->n; i++) {
        fprintf(stderr, "%d: ", i);

        e = D->T->verts[i].edgelist.head;
        while (NULL != e) {
            fprintf(stderr, "--(%d)--> %d,      ", e->w, e->v);
            e = e->next;
        }
        fprintf(stderr, "\n");
    }

    fprintf(stderr, "\n");
    return;
}












