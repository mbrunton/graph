/* priority_queue.c

*/

#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

pq_t *
create_empty_pq(int length, size_t data_size) {
    pq_t *Q = (pq_t *) malloc(sizeof(pq_t));
    if (NULL == Q) {
        fprintf(stderr, "%s: malloc failed on line %d\n", __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }

    Q->entries = (entry_t *) malloc(data_size * length);
    if (NULL == Q->entries) {
        fprintf(stderr, "%s: malloc failed on line %d\n", __FILE__, __LINE__);
    }

    Q->size = 0;
    Q->capacity = data_size * length;

    int i;
    for (i = 0; i < length; i++) {
        Q->entries[i].data = NULL;
        Q->entries[i].p = UNDEFINED;
    }
    return Q;
}
