/* queue.c
   implementation of a queue
*/

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

queue_t *
create_empty_queue(void) {
    queue_t *Q = (queue_t *) malloc(sizeof(queue_t));
    if (NULL == Q) {
        fprintf(stderr, "Error: malloc failed\n");
        exit(EXIT_FAILURE);
    }

    Q->head = NULL;
    Q->tail = NULL;
    Q->size = 0;
    return Q;
}

void
q_push(queue_t *Q, void *data) {

    item_t *new_entry = (item_t *) malloc(sizeof(item_t));
    if (NULL == new_entry) {
        fprintf(stderr, "Error: malloc failed\n");
        exit(EXIT_FAILURE);
    }

    new_entry->data = data;
    new_entry->next = NULL;

    if (0 == Q->size) {
        Q->head = Q->tail = new_entry;
    } else {
        Q->tail->next = new_entry;
        Q->tail = Q->tail->next;
    }

    Q->size++;
}

void *
q_pop(queue_t *Q) {
    if (0 == Q->size) {
        fprintf(stderr, "Error: attempting to pop empty queue\n");
        fprintf(stderr, "file: %s\tline: %d\n", __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }

    item_t *old_head = Q->head;
    void *data = Q->head->data;
    
    if (1 == Q->size) {
        Q->head = Q->tail = NULL;
    } else {
        Q->head = Q->head->next;
    }

    Q->size--;
    free(old_head);
    return data;
}

void *
q_peek(queue_t *Q) {
    if (0 == Q->size) {
        fprintf(stderr, "Error: attempting to peek empty queue\n");
        fprintf(stderr, "file: %s\tline: %d\n", __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }

    return Q->head->data;
}

int
q_not_empty(queue_t *Q) {
    return Q->size != 0;
}

// TODO: this is just for debugging purposes (I know data will be an int *)
// is there a way to pass to this function what type void * points to?
void
print_queue(queue_t *Q) {
    fprintf(stderr, "QUEUE PRINTOUT:\n");
    if (Q->size == 0) {
        fprintf(stderr, "(queue empty)\n");
    }

    item_t *curr;
    int *value;
    for (curr = Q->head; curr != NULL; curr = curr->next) {
        value = (int *) curr->data;
        fprintf(stderr, "%d\n", *value);
    }
    fprintf(stderr, "\n");
}











