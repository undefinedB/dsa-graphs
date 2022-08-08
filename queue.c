#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue.h>

//functiile uzuale

queue *create_queue(pair *data)
{
    queue *q = malloc(sizeof(queue));
    q->first = malloc(sizeof(qnode));
    q->first->next = NULL;
    q->first->data = data;
    q->last = q->first;
    return q;
}

queue *enqueue(queue *q, pair *data)
{
    qnode *new = malloc(sizeof(qnode));
    new->data = data;
    new->next = NULL;
    if(q->first == NULL) {
        q->first = new;
        q->last = new;
        return q;
    }
    q->last->next = new;
    q->last = new;
    return q;
}

pair *dequeue(queue *q)
{
    pair *x = q->first->data;
    qnode *p = q->first->next;
    free(q->first);
    q->first = p;
    return x;
}

pair *create_pair(int nod, unsigned int mask)
{
    pair *p = malloc(sizeof(pair));
    p->n = nod;
    p->bitmask = mask;
    return p;
}

int isEmpty(queue *q)
{
    if(q->first == NULL) return 1;
    return 0;
}
