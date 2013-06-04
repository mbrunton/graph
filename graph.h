/* graph.h - header file for graph.c
   suit of function prototypes
   for common graph algorithms
*/

#include <stdlib.h>

typedef struct edge_t {
    int u;
    int v;
    int w;
    struct edge_t *next;
} edge_t;

typedef struct {
    edge_t *head;
} edgelist_t;

typedef struct {
    edgelist_t edgelist;
} vertex_t;

typedef struct {
    vertex_t *verts;
    int n;
} graph_t;

// INITIALISATIONS
graph_t *read_graph(char *filename);
graph_t *create_empty_graph(int n);
void insert_edge(graph_t *G, int u, int v, int w);
void print_graph(graph_t *G);


// SEARCHING
void dfs(graph_t *G);
void bfs(graph_t *G);

// DISTANCES
int *dijkstra(graph_t *G);
int *bellman_ford(graph_t *G);

// TREES
graph_t *kruskal(graph_t *G);
graph_t *primm(graph_t *G);
