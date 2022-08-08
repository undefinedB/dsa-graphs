#include <stdio.h>
#include <stdlib.h>
#include <binary_heap.h>
#include <graf.h>
#include <queue.h>
#include <math.h>
#define FLOAT_MAX 3.402823466E+38

//algoritmul dijksta modificat
//primeste subgraful care codifica 1, daca nodul e in graf si 
//0 daca nu e
float modified_dijkstra(graf *g, char *subgraf, char *e_dep)
{
    //vectorul de distante, care retine pe linie nodul curent
    //pe coloana bitmaskul
    unsigned int mask = 0;
    float **dist = malloc(g->n * sizeof(float *));
    for(int i = 0; i < g->n; i++) {
        dist[i] = malloc((1 << g->n) * sizeof(float));
        if(subgraf[i]) mask += 1 << i;
    }

    //am construit mai sus masca astfel incat sa reprezinte exact
    //masca nodurilor ce trebuie atinse

    float min = FLOAT_MAX;
    
    //plec din fiecare depozit si incerc sa ajung inapoi in el
    //la final, fac maximul
    
    //ma misc doar pe depozite si pe nodurile din subgraf
    //iau pe rand toate depozitele

    for(int i = 0; i < g->n; i++) {
        //daca nu e depozit, nu mai fac mutarile
        if(!e_dep[i]) continue;

        //daca e depozit, pornesc dijkstra
        //starea de final are masca mask si 
        //se afla in nodul din care s-a plecat
        int nodplecare = i;

        //initializarea distantelor
        for(int j = 0; j < g->n; j++)
            for(int k = 0; k < (1 << g->n); k++)
                dist[j][k] = FLOAT_MAX;
        dist[i][0] = 0;

        //daca e depozit, incep cu masca 0
        pair *data = create_pair(i, 0);
        queue *q = create_queue(data);

        while(!isEmpty(q)) {
            pair *current = dequeue(q);
            //ma mut pe nodurile adiacente
            node *p = g->adj[current->n];
            while(p!=NULL) {
                int neigh = p->nod;
                float cost = p->cost;
                unsigned int or_mask;
                //daca nu e depozit sau nu e in subgraf, dau continue
                if(!e_dep[neigh] && !subgraf[neigh]) {
                    p = p->next;
                    continue;
                }
                if(e_dep[neigh]) or_mask = 0;
                else or_mask = 1 << neigh;

                //bag in coada doar daca gasesc pe perechea respectiva
                //o valoare mai mica
                if(dist[neigh][or_mask | current->bitmask] > 
                cost + dist[current->n][current->bitmask]) {
                    pair *x = create_pair(neigh, or_mask | current->bitmask);
                    enqueue(q, x);
                    dist[neigh][or_mask | current->bitmask] = 
                    cost + dist[current->n][current->bitmask];
                }

                p = p->next;
            }

            free(current);
        }
        free(q);
        //retin in min minimul
        if(min > dist[nodplecare][mask]) min = dist[nodplecare][mask];
    }

    for(int j = 0; j < g->n; j++)
        free(dist[j]);
    free(dist);
    
    return min;
}
