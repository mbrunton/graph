/* graph.h - header file for graph.c
   suit of function prototypes
   for common graph algorithms
*/

#include <stdlib.h>

#define DIRECTED 0
#define MAX_LINE 80
#define UNDEFINED -1
#define TRUE (1==1)
#define FALSE (1==0)

// GRAPH TYPEDEFS
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
    int directed;
} graph_t;


// DFS TYPEDEFS
typedef struct {
    graph_t *T; // dfs tree (really a forest)
    int *parents;
    int *dfi_array;
    int dfi_counter;
    int k;  // number of components
} dfs_struct;


// INITIALISATIONS
graph_t *read_graph(char *filename);
graph_t *create_empty_graph(int n, int directed);

// PRINTING
void print_graph(graph_t *G);
void print_dfs(dfs_struct *D);


// SEARCHING    TODO pass function pointer to act on each explored node
dfs_struct *dfs(graph_t *G);
graph_t *bfs(graph_t *G);

// DISTANCES
int *dijkstra(graph_t *G);
int *bellman_ford(graph_t *G);

// TREES
graph_t *kruskal(graph_t *G);
graph_t *primm(graph_t *G);
