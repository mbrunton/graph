/* priority_queue.h
   header file for priority_queue.c
   this file contains typedefs and function prototypes which describe
   priority queue operations
*/
// TODO: function pointers for priority comparison?

#define LEFT(i) (2*(i) + 1)
#define RIGHT(i) (2*(i) + 2)
#define PARENT(i) ( ((i)-1)/2 )

#define UNDEFINED -1
#define TRUE (1==1)
#define FALSE (1==0)

typedef struct {    // entry_t holds pointer to data item, and corresponding priority
    void *data;
    int p;
} entry_t;

typedef struct {
    size_t size;    // current number of entries
    size_t capacity;    // total number of allowed entries
    entry_t *entries;   // array of entry_t
} pq_t;

// TODO: shouldn't have to supply length.. make a variable array
pq_t *create_empty_pq(int length);
void pq_push(pq_t *Q, void *data, int priority);
void update_priority(pq_t *Q, void *data, int priority);
void *pq_pop(pq_t *Q);
void *pq_peek(pq_t *Q);
void print_pq(pq_t *Q);
