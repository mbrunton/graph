/* graph.c
   implements functions described in graph.h
   for performing common algorithms on graphs
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"
#include "priority_queue.h"
#include "queue.h"


// AUXILIARY FUNCTIONS
graph_t *create_empty_graph(int n, int directed);
void insert_edge(graph_t *G, int u, int v, int w);
search_tree_t *create_empty_search_tree(int n);
void explore(graph_t *G, search_tree_t *D, int u);
search_tree_t *dfs_rec(graph_t *G);
search_tree_t *dfs_iter(graph_t *G);
int *get_vertex_array(int n);
dist_tree_t *create_empty_dist_tree(int n, int s);

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
    G->edgelists = (edgelist_t *) malloc(sizeof(edgelist_t) * n);

    int i;
    for (i=0; i<n; i++) {
        G->edgelists[i].head = NULL;
    }

    return G;
}

void
insert_edge(graph_t *G, int u, int v, int w) {
    edge_t *e = G->edgelists[u].head;
    
    if (NULL == e) {
        // first edge off this vertex
        G->edgelists[u].head = (edge_t *) malloc(sizeof(edge_t));
        G->edgelists[u].head->u = u;
        G->edgelists[u].head->v = v;
        G->edgelists[u].head->w = w;
        G->edgelists[u].head->next = NULL;
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
search_tree_t *
dfs(graph_t *G) {
    if (REC_DFS == 1) {
        return dfs_rec(G);
    } else {
        return dfs_iter(G);
    }
}

/* recursive implementation of depth-first search */
search_tree_t *
dfs_rec(graph_t *G) {
    search_tree_t *D = create_empty_search_tree(G->n);

    int i;
    for (i = 0; i < G->n; i++) {
        if (D->arrival_times[i] == UNDEFINED) {
            explore(G, D, i);
            D->k++;
        }
    }

    return D;
}

void
explore(graph_t *G, search_tree_t *D, int u) {
    // mark vertex u as visited
    D->arrival_times[u] = D->arrival_counter;
    D->arrival_counter++;

    // explore an unvisited neighbor (if exists)
    int v;
    edge_t *e = G->edgelists[u].head;
    while (NULL != e) {
        v = e->v;
        if (D->arrival_times[v] == UNDEFINED) {
            // add edge e to our forest and start exploring v
            insert_edge(D->T, e->u, e->v, e->w);
            D->parents[v] = u;
            explore(G, D, v);
        }
        e = e->next;
    }
    return;
}

/* iterative implementation of depth-first search */
search_tree_t *
dfs_iter(graph_t *G) {

    search_tree_t *D = create_empty_search_tree(G->n);
    int u;  // u is active vertex
    int v;      // v is a neighbor of u
    edge_t *e;

    // TODO: fix dfi bug
    for (u = 0; u < G->n; u++) {
        if (D->arrival_times[u] == UNDEFINED) {
            D->k++;
            while (TRUE) {
                D->arrival_times[u] = D->arrival_counter;
                D->arrival_counter++;

                // explore first unvisited neighbor (if exists)
                e = G->edgelists[u].head;
                while (NULL != e) {
                    v = e->v;
                    if (D->arrival_times[v] == UNDEFINED) {
                        insert_edge(D->T, e->u, e->v, e->w);
                        D->parents[v] = u;
                        u = v;
                        break;
                    }
                    e = e->next;
                }
                
                if (NULL == e) {
                    // got to end of edgelist, all neighbors visited
                    if (D->parents[u] != UNDEFINED) {
                        u = D->parents[u];  // backtrack to parent of u
                    } else {
                        break;  // we're back at root
                    }
                }
            }
        }
    }

    return D;
}

search_tree_t *
create_empty_search_tree(int n) {
    search_tree_t *D = (search_tree_t *) malloc(sizeof(search_tree_t));

    // TODO: tree should only have n vertices if underlying graph is connected
    D->T = create_empty_graph(n, FALSE); // TODO: directed or undirected?
    D->parents = (int *) malloc(sizeof(int) * n);
    D->arrival_times = (int *) malloc(sizeof(int) * n);
    D->arrival_counter = 0;
    D->k = 0;

    int i;
    for (i = 0; i < n; i++) {
        D->parents[i] = UNDEFINED;
        D->arrival_times[i] = UNDEFINED;
    }
    return D;
}

search_tree_t *
bfs(graph_t *G) {
    search_tree_t *D = create_empty_search_tree(G->n);
    queue_t *Q = create_empty_queue();

    // create array of vertex ints since queue stores (void *) pointers
    int *vertices = get_vertex_array(G->n);

    int u;  // active vertex
    int v;  // neighboring vertex
    edge_t *e;

    int i;
    for (i = 0; i < G->n; i++) {
        if (D->arrival_times[i] == UNDEFINED) {
            // push root node i onto queue and start bfs
            q_push(Q, (void *) &vertices[i]);
            D->arrival_times[i] = D->arrival_counter;
            D->arrival_counter++;
            D->k++;

            while (q_not_empty(Q)) {
                u = *( (int *) q_pop(Q) );
                e = G->edgelists[u].head;
                while (NULL != e) {
                    v = e->v;
                    if (D->arrival_times[v] == UNDEFINED) {
                        D->arrival_times[v] = D->arrival_counter;
                        D->arrival_counter++;
                        D->parents[v] = u;
                        insert_edge(D->T, e->u, e->v, e->w);
                        q_push(Q, (void *) &vertices[v]);
                    }
                    e = e->next;
                }
            }
        }
    }

    return D;
}

// return array {0, 1, ..., n-1}
int *
get_vertex_array(int n) {
    int *vertices = (int *) malloc(sizeof(int) * n);
    if (NULL == vertices) {
        fprintf(stderr, "Error: malloc failed\n");
        exit(EXIT_FAILURE);
    }
    int i;
    for (i = 0; i < n; i++) {
        vertices[i] = i;    
    }

    return vertices;
}

// TODO: fix bugs
dist_tree_t *
dijkstra(graph_t *G, int s) {

    pq_t *pq = create_empty_pq(G->n);
    int *vertices = get_vertex_array(G->n);
    dist_tree_t *D = create_empty_dist_tree(G->n, s);

    // store all vertices in priority queue
    int i;
    for (i = 0; i < G->n; i++) {
        pq_push(pq, &vertices[i], D->dists[i]);
    }

    int u;  // active vertex
    int v;  // neighboring vertex
    int d;   // final distance of active vertex
    edge_t *e;
    while (pq_not_empty(pq)) {
        // pop top vertex and record final distance
        d = pq_peek_priority(pq);
        u = *( (int *) pq_pop(pq) );
        D->dists[u] = d;

        // go through neighbors and see if route through u is quicker than current estimate
        e = G->edgelists[u].head;
        while (NULL != e) {
            if (e->w < 0) {
                fprintf(stderr, "Error: dijkstra's algorithm cannot ");
                fprintf(stderr, "be applied to negatively weighted graphs\n");
                exit(EXIT_FAILURE);
            }
            v = e->v;
            if (d + e->w < D->dists[v]) {
                D->dists[v] = d + e->w;
                D->parents[v] = u;
                update_priority(pq, &vertices[v], D->dists[v]);
            }
            e = e->next;
        }
        
    }

    return D;
}

dist_tree_t *
create_empty_dist_tree(int n, int s) {
    dist_tree_t *D = (dist_tree_t *) malloc(sizeof(dist_tree_t));
    if (NULL == D) {
        fprintf(stderr, "Error: malloc failed\n");
        exit(EXIT_FAILURE);
    }

    D->s = s;
    D->n = n;
    D->dists = (int *) malloc(sizeof(int) * n);
    D->parents = (int *) malloc(sizeof(int) * n);
    if (NULL == D->dists || NULL == D->parents) {
        fprintf(stderr, "Error: malloc failed\n");
        exit(EXIT_FAILURE);
    }

    int i;
    for (i = 0; i < n; i++) {
        if (i == s) {
            D->dists[i] = 0;
        } else {
            D->dists[i] = INFINITY;
        }
        D->parents[i] = UNDEFINED;
    }

    return D;
}

void
print_graph(graph_t *G) {
    int i;
    edge_t *e;
    fprintf(stderr, "GRAPH PRINTOUT:\n");
    fprintf(stderr, "n = %d\n", G->n);
    if (G->directed) {
        fprintf(stderr, "(directed)\n");
    } else {
        fprintf(stderr, "(undirected)\n");
    }

    for (i = 0; i < G->n; i++) {
        fprintf(stderr, "%d:  ", i);

        e = G->edgelists[i].head;
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
print_search_tree(search_tree_t *D) {
    int i;
    edge_t *e;
    fprintf(stderr, "SEARCH PRINTOUT:\n");
    fprintf(stderr, "k = %d\n", D->k);

    for (i = 0; i < D->T->n; i++) {
        fprintf(stderr, "%d: ", i);

        if (D->parents[i] == UNDEFINED) {
            fprintf(stderr, "(root), ");
        } else {
            fprintf(stderr, "parent = %d, ", D->parents[i]);
        }
        fprintf(stderr, "arrival time = %d\n", D->arrival_times[i]);
    }
    fprintf(stderr, "\n");

    for (i = 0; i < D->T->n; i++) {
        fprintf(stderr, "%d: ", i);

        e = D->T->edgelists[i].head;
        while (NULL != e) {
            fprintf(stderr, "--(%d)--> %d,      ", e->w, e->v);
            e = e->next;
        }
        fprintf(stderr, "\n");
    }
    fprintf(stderr, "\n");
}

void
print_dist_tree(dist_tree_t *D) {
    fprintf(stderr, "DISTANCE PRINTOUT:\n");
    fprintf(stderr, "source node = %d\n", D->s);

    int i;
    for (i = 0; i < D->n; i++) {
        fprintf(stderr, "dist[%d] = %d\n", i, D->dists[i]);
    }
    fprintf(stderr, "\n");
}










