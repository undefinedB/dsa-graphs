#include <stdio.h>
#include <stdlib.h>
#include <graf.h>
#include <binary_heap.h>

//extern void swap(int *a, int *b);

//implementarea grafului foloseste liste
//de adiacenta
//restul functiilor sunt cunoscute, folosite
//in teme si in laboratoare
node *new_list(int nod, float cost)
{
    node *l = malloc(sizeof(node));
    l->nod = nod;
    l->cost = cost;
    l->next = NULL;
    return l;
}

void free_list(node **l)
{
    node *p = *l;
    while(p != NULL)
    {
        p = (*l)->next;
        free(*l);
        *l = p;
    }
}

void add_node(node **l, int nod, float cost)
{
    if((*l) == NULL) {
        (*l) = new_list(nod, cost);
        return;
    }

    node *new = new_list(nod, cost);
    new->next = (*l);
    *l = new;
}


graf *create_graf(int nodes)
{
    graf *g = malloc(sizeof(graf));
    g->n = nodes;
    g->adj = calloc(nodes, sizeof(node *));

    return g;
}

void add_edge(graf *g, int nod1, int nod2, float cost) 
{
    add_node(g->adj + nod1, nod2, cost);
}

void print_graf(graf *g)
{
    for(int i = 0; i < g->n; i++)
    {
        printf("vecinii lui %d:\n", i);
        node *p = g->adj[i];//pentru ca am dat calloc
        //ele sunt initializate cu 0, deci daca nodul nu exista
        //p e null
        while(p != NULL) {
            printf("%d %.1f\n", p->nod, p->cost);
            p = p->next;
        }
    }
}

//functie de eliberare a memoriei
void collapse_graf(graf *g)
{
    for(int i = 0; i < g->n; i++)
        free_list(g->adj + i);
    free(g->adj);
    free(g);
}

//inverseaza un array incepand de la indexul start
//pana la finish
//folosesc functia pentru drumuri

void invert_array(int *path, int start, int finish)
{
    int mid = (start + finish)/2;
    for(int i = start; i < mid; i++) {
        swap(path + i, path + start + finish - i - 1);
    }
}

//primesc vectori de dati facut din dijkstra si construiesc intr-un vector calea
void construct_path(int *start, int *finish, int *final_path, int *dijkstra_path, int nodstart, int ignore_last_node)
{
    *finish = *start;
    int i = nodstart;

    while(i != -1) {
        final_path[*finish] = i;
        i = dijkstra_path[i];
        *finish = *finish + 1;
    }
    if(ignore_last_node) (*finish)--;
    invert_array(final_path, *start, *finish);
}

//functie care gaseste si afiseaza toate componentele
//tari conexe
void strongly_connected(graf *g, char *e_dep)
{
    int comp = 0;
    char *viz = calloc(g->n * sizeof(char), 1);
    int *v = calloc(g->n, sizeof(int));

    for(int i = 0; i < g->n; i++) {
        if(e_dep[i]) continue;
        if(!viz[i]) {
            comp ++;
            dfs(g, viz, comp, v, i, e_dep);
        }
    }

    printf("%d\n", comp);

    for(int i = 1; i <= comp; i++) {
        //if(e_dep[i]) continue;
        int nr = 0;
        for(int j = 0; j < g->n; j++) {
            if(v[j] == i) nr++;
        }
        for(int j = 0; j < g->n; j++) {
            if(v[j] == i && nr > 1) {
                nr--;
                printf("%d ", j);
            }
            else if (v[j] == i) printf("%d", j);
        }
        if(i!=comp)
            printf("\n");
    }

    free(viz);
    free(v);
}

void dfs(graf *g, char *viz, int comp, int *v, int current, char *e_dep)
{
    v[current] = comp;
    node *p = g->adj[current];
    while(p!=NULL) {
        //is_connected e folosita pentru a verifica daca se poate ajunge si din current
        //la depozit
        if(!viz[p->nod] && !e_dep[p->nod] && is_connected(g, p->nod, current, e_dep)) {
            viz[p->nod] = 1;
            dfs(g, viz, comp, v, p->nod, e_dep);
        }
        p = p->next;
    }
}

//verifica daca in graf poti ajunge de la nod1 la nod2
//NU TRECE prin depozite
int is_connected(graf *g, int nod1, int nod2, char *e_dep)
{
    char *viz = calloc(g->n * sizeof(char), 1);
    float *d = malloc(g->n * sizeof(float));
    for(int j = 1; j < g->n; j++)
        d[j] = j;

    binary_heap *h = create_heap(g->n);
    add_to_binary_heap(h, nod1, d);
    while(h->curr) {
        int nodcurent = remove_from_binary_heap(h, d);
        node *p = g->adj[nodcurent];

        while(p!=NULL) {
            if(!viz[p->nod] && !e_dep[p->nod]) {
                if(p->nod == nod2) {
                    free(h->heap);
                    free(h->map);
                    free(h);
                    free(d);
                    free(viz);
                    return 1;
                }
                viz[p->nod] = 1;
                add_to_binary_heap(h, p->nod, d);
            }
            p = p->next;
        }
    }
    free(h->heap);
    free(h->map);
    free(h);
    free(d);
    free(viz);

    return 0;
}
