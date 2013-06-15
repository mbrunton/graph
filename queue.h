/* queue.h
   header file for queue.c
*/

typedef struct {
    void **data;    // array of (void *)
    int head;
    int tail;
    int size;
    int capacity;
} queue_t;

queue_t *create_empty_queue(int length);
void push(queue_t *Q, void *item);
queue_t *pop(queue_t *Q);
