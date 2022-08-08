#include <stdio.h>
#include <stdlib.h>
#include <binary_heap.h>

void swap(int *a, int *b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}

//implementare minheap

int parent(int i)
{
    return (i-1)/2;
}

int left(int i) 
{ 
    return (2*i + 1);
}

int right(int i) 
{ 
    return (2*i + 2);
}

//functiile de implementare a heapului
//singura diferenta este faptul ca folosesc
//un heap special pentru dijkstra
//in care dau ca parametru si vectorul de distante
//cu care fac comparatiile

binary_heap *create_heap(int max)
{
    binary_heap *h = malloc(sizeof(binary_heap));
    h->n = max;
    h->curr = 0;
    h->heap = malloc(max * sizeof(int));
    h->map = malloc(max * sizeof(int));
    return h;
}

void add_to_binary_heap(binary_heap *h, int x, float *d)
{
    (h->curr)++;//incrementez valoarea nr curent de elem
    h->heap[(h->curr) - 1] = x;//pun la final x

    int cpos = h->curr - 1;//pozitia curenta din vector,
    h->map[x] = cpos;
    //inainte de cernere
    while(cpos && d[h->heap[parent(cpos)]] > d[h->heap[cpos]]) {
        swap(&h->heap[parent(cpos)], &h->heap[cpos]);
        swap(h->map + parent(cpos), h->map + cpos);
        cpos = parent(cpos);
        //if(parent(cpos) < 0) return;
    }
}

int remove_from_binary_heap(binary_heap *h, float *d)
{
    int out = h->heap[0];
    h->map[out] = 0;
    swap(h->heap, h->heap + h->curr - 1);
    (h->curr)--;

    int cpos = 0;//pozitia curenta inainte de cernere

    while(cpos < h->curr){
        if(right(cpos) < h->curr)
            if(d[h->heap[right(cpos)]] < d[h->heap[cpos]])
                {
                    swap(&h->heap[right(cpos)], &h->heap[cpos]);
                    swap(h->map + right(cpos), h->map + cpos);
                    cpos = right(cpos);
                    continue;
                }
        if(left(cpos) < h->curr) 
            if(d[h->heap[left(cpos)]] < d[h->heap[cpos]])
                {
                    swap(&h->heap[left(cpos)], &h->heap[cpos]);
                    swap(h->map + left(cpos), h->map + cpos);
                    cpos = left(cpos);
                    continue;
                }
        break;
    }

    return out;
}

void print_array(int *array, int n)
{
    for(int i = 0; i < n - 1; i++)
        printf("%d ", array[i]);
    printf("%d", array[n - 1]);
    printf("\n");
}

//ia un element din heap si ii updateaza prioritatea
//in timpul algoritmului dijkstra modific uneori 
//un element si pentru ca e deja in heap, prioritatea
//nu i se schimba
void increase_priority(binary_heap *h, int x, float *d)
{
    int cpos = x;
    while(cpos && d[h->heap[parent(cpos)]] > d[h->heap[cpos]]) {
        swap(&h->heap[parent(cpos)], &h->heap[cpos]);
        swap(h->map + parent(cpos), h->map + cpos);
        cpos = parent(cpos);
    }
}