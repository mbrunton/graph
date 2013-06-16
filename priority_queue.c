/* priority_queue.c

*/

#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

pq_t *
create_empty_pq(int length) {
    // TODO: check malloc succeeded
    pq_t *Q = (pq_t *) malloc(sizeof(pq_t));
    Q->entries = (entry_t *) malloc(sizeof(entry_t) * length);

    Q->size = 0;
    Q->capacity = length;

    int i;
    for (i = 0; i < length; i++) {
        Q->entries[i].data = NULL;
        Q->entries[i].p = UNDEFINED;
    }
    return Q;
}

void
pq_push(pq_t *Q, void *data, int priority) {
    if (Q->size >= Q->capacity) {
        fprintf(stderr, "Error: priority queue is full\n");
        fprintf(stderr, "file: %s\tline: %d\n", __FILE__, __LINE__);
    }

    // insert new entry at end of array
    int i = Q->size;
    Q->entries[i].data = data;
    Q->entries[i].p = priority;
    Q->size++;

    // swap added entry with parent while it's out of order
    entry_t temp_entry;
    while ( PARENT(i) >= 0 && Q->entries[i].p < Q->entries[ PARENT(i) ].p ) {
        temp_entry = Q->entries[ PARENT(i) ];
        Q->entries[ PARENT(i) ] = Q->entries[i];
        Q->entries[i] = temp_entry;
        i = PARENT(i);
    }
}

// TODO: make sure only distinct items?
void
update_priority(pq_t *Q, void *data, int priority) {
    int i;
    for (i = 0; i < Q->size; i++) {
        if (Q->entries[i].data == data) {
            Q->entries[i].p = priority;
            break;
        }
    }

    if (i == Q->size) {
        fprintf(stderr, "Error: could not locate item in priority queue\n");
        fprintf(stderr, "file: %s\tline: %d\n", __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }
}

void *
pq_pop(pq_t *Q) {
    if (Q->size <= 0) {
        fprintf(stderr, "Error: priority queue is empty\n");
        fprintf(stderr, "file: %s\tline:%d\n", __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }

    // latch onto (void *) at top of heap
    void *top = Q->entries[0].data;

    // move end of heap onto top
    Q->entries[0] = Q->entries[Q->size - 1];
    Q->entries[Q->size - 1].data = NULL;
    Q->entries[Q->size - 1].p = UNDEFINED;
    Q->size--;

    // TODO: refactor this loop.. it's ugly looking
    entry_t temp_entry;
    int min_p;
    int min_child;
    int i = 0;
    while (TRUE) {
        if ( LEFT(i) < Q->size ) {
            if ( RIGHT(i) < Q->size ) {
                // both children are present.. find smaller of the two
                if (Q->entries[LEFT(i)].p <= Q->entries[RIGHT(i)].p) {
                    min_p = Q->entries[LEFT(i)].p;
                    min_child = LEFT(i);
                } else {
                    min_p = Q->entries[RIGHT(i)].p;
                    min_child = RIGHT(i);
                }
                if (Q->entries[i].p > min_p) {
                    // swap
                    temp_entry = Q->entries[min_child];
                    Q->entries[min_child] = Q->entries[i];
                    Q->entries[i] = temp_entry;
                    i = min_child;
                } else {
                    break;
                }
            } else {
                // only left child is present
                if (Q->entries[i].p > Q->entries[LEFT(i)].p) {
                    // swap
                    temp_entry = Q->entries[LEFT(i)];
                    Q->entries[LEFT(i)] = Q->entries[i];
                    Q->entries[i] = Q->entries[LEFT(i)];
                    i = LEFT(i);
                } else {
                    break;
                }
            }
        } else {
            // no children are present
            break;
        }
    }

    return top;
}

/* get data item with lowest priority without removing from priority queue */
void *
pq_peek(pq_t *Q) {
    if (Q->size <= 0) {
        fprintf(stderr, "Error: priority queue is empty\n");
        fprintf(stderr, "file: %s\tline:%d\n", __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }

    return Q->entries[0].data;
}

/* get priority of item at top of priority queue */
int
pq_peek_priority(pq_t *Q) {
    if (Q->size <= 0) {
        fprintf(stderr, "Error: priority queue is empty\n");
        fprintf(stderr, "file: %s\tline:%d\n", __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }

    return Q->entries[0].p;
}

/* return true if priority queue has >= 1 item */
int
pq_not_empty(pq_t *Q) {
    return Q->size != 0;
}

void
print_pq(pq_t *Q) {
    fprintf(stderr, "PRIORITY QUEUE PRINTOUT:\n");
    if (Q->size == 0) {
        fprintf(stderr, "(queue empty)\n");
    }

    int i;
    for (i = 0; i < Q->size; i++) {
        fprintf(stderr, "item #%d: p = %d\n", i, Q->entries[i].p);
    }
    fprintf(stderr, "\n");
}



