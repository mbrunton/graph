/* queue.h
   header file for queue.c
*/

typedef struct item_t {
    void *data;
    struct item_t *next;
} item_t;

typedef struct {
    item_t *head;
    item_t *tail;
    int size;
} queue_t;

queue_t *create_empty_queue(void);
void q_push(queue_t *Q, void *data);
void *q_pop(queue_t *Q);
void *q_peek(queue_t *Q);
void print_queue(queue_t *Q);
