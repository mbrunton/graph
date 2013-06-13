/* priority_queue.h
   header file for priority_queue.c
   this file contains typedefs and function prototypes which describe
   priority queue operations
*/
// TODO: function pointers for priority comparison?

// TODO: problem redefining from graph.h?
#define UNDEFINED -1

#define LEFT(i) (2*(i) + 1)
#define RIGHT(i) (2*(i) + 2)
#define PARENT(i) ( ((i)-1)/2 )

typedef struct {    // entry_t holds pointer to data item, and corresponding priority
    void *data;
    int p;
} entry_t

typedef struct {
    size_t size;    // amount of space pq is taking up
    size_t capacity;    // total allocated space
    entry_t *entries;   // array of entry_t
} pq_t;

pq_t *create_empty_pq(int length, size_t data_size);
void push(void *data, int priority);
void update_priority(void *data, int priority);
void *pop();
void *peek();

