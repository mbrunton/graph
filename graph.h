/* graph.h - header file for graph.c
   suit of function prototypes
   for common graph algorithms
*/

#include <stdlib.h>

#define INFINITY (1000*1000*1000)
#define DIRECTED 0
#define MAX_LINE 80
#define UNDEFINED -1
#define TRUE (1==1)
#define FALSE (1==0)
// TODO: find a better way of meta-branching
#define REC_DFS 1   // 1/0 for recursive/iterative implementation of dfs

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
    edgelist_t *edgelists;  // an array of edgelists
    int n;                  // order of graph
    int directed; 
} graph_t;


// SEARCH TYPEDEFS
// TODO: backedges
typedef struct {
    graph_t *T; // dfs tree
    int *parents;
    int *arrival_times;
    int arrival_counter;
    int k;  // number of components
} search_tree_t;

typedef struct {
    int s;  // source
    int n;  // order of graph
    int *dists;
    int *parents;
} dist_tree_t;

// INITIALISATIONS
graph_t *read_graph(char *filename);

// PRINTING
void print_graph(graph_t *G);
void print_search_tree(search_tree_t *D);
void print_dist_tree(dist_tree_t *D);

// SEARCHING    
// TODO: pass function pointer to act on each visited node
// TODO: have source node option as well
search_tree_t *dfs(graph_t *G);
search_tree_t *bfs(graph_t *G);

// DISTANCES
dist_tree_t *dijkstra(graph_t *G, int s);
int *bellman_ford(graph_t *G);

// TREES
graph_t *kruskal(graph_t *G);
graph_t *primm(graph_t *G);



