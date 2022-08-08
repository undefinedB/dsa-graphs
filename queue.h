#ifndef __queue__
#define __queue__

//implementarea unei cozi
//ce tine cate o pereche
typedef struct pair{
    int n;//nod
    unsigned int bitmask;//masca de bytes
} pair;

typedef struct qnode{
    pair *data;
    struct qnode * next;
} qnode;

typedef struct queue{
    qnode *first;
    qnode *last;
} queue;

queue *create_queue(pair *data);
queue *enqueue(queue *q, pair *data);
pair *dequeue(queue *q);
pair *create_pair(int nod, unsigned int mask);
int isEmpty(queue *q);

#endif