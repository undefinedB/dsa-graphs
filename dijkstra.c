#include <stdio.h>
#include <stdlib.h>
#include <binary_heap.h>
#include <graf.h>
#define FLOAT_MAX 3.402823466E+38

//algoritmul dijksta
//a fost prezentat la curs
//implementarea mea doar foloseste heap(mai rapid)
//si scoate, pe langa vectorul de distante, si vectorul
//path(folositor pentru a determina drumul)

//practic dijkstra + vector de tati
float *dijkstra(graf *g, int source, int *path)
{
    float *d = malloc(g->n * sizeof(float));
    int *viz = calloc(g->n * sizeof(int), 1);
    for(int i = 0; i < g->n; i++)
        path[i] = -1;

    for(int i = 0; i < g->n; i++)
        d[i] = FLOAT_MAX;
    d[source] = 0;
    viz[source] = 1;

    binary_heap *h = create_heap(g->n);
    add_to_binary_heap(h, source, d);

    while(h->curr != 0) {
        int current = remove_from_binary_heap(h, d);
        viz[current] = 0;
        node *p = g->adj[current];

        while(p != NULL) {
            int neigh = p->nod;
            float cost = p->cost;
            viz[neigh] = 0;

            if(d[neigh] > d[current] + cost) {
                d[neigh] = d[current] + cost;
                path[neigh] = current;
                if(!viz[neigh]) {
                    viz[neigh] = 1;
                    add_to_binary_heap(h, neigh, d);
                }
                else {
                    increase_priority(h, h->map[neigh], d);
                }
            }
            p = p->next;
        }
    }

    free(h->heap);
    free(h->map);
    free(h);
    free(viz);
    return d;
}
