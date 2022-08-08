#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graf.h>
#include <binary_heap.h>

extern float *dijkstra(graf *g, int source, int *path);
extern float modified_dijkstra(graf *g, char *subgraf, char *e_dep);

//citirile sunt facute conform cerintei

int main()
{
    int n, m, nrdep, nr_task;
    scanf("%d%d%d", &n, &m, &nrdep);
    char *e_dep = calloc(sizeof(int), n);//verifica daca e depozit
    graf *g = create_graf(n);

    for(int i = 0; i < m; i++) {
        int x, y;
        float cost;
        scanf("%d%d%f", &x, &y, &cost);
        add_edge(g, x, y, cost);
    }

    for(int i = 0; i < nrdep; i++) {
        int x;
        scanf("%d", &x);
        e_dep[x] = 1;
        //printf("%d\n", x);
    }

    scanf("%d", &nr_task);

    for(int i = 0; i < nr_task; i++) {
        char buffer[10];
        scanf("%s", buffer);
        int *path = malloc(sizeof(int) * n);

        if(!strcmp("e1", buffer)) {
            int dep, k;
            scanf("%d%d", &dep, &k);
            float total = 0;

            for(int j = 0; j < k; j++) {
                int nod;
                scanf("%d", &nod);
                printf("%d\n", nod);
                float *d = dijkstra(g, dep, path);
                int *final_path = malloc(2 * n * sizeof(int));
                int finish;
                int start = 0;

                //construiesc path si de la nod la depozit
                //si de la depozit la nod
                //am grija ca la intors sa nu dublez depozitul
                total += d[nod];
                printf("%.1f ", d[nod]);
                construct_path(&start, &finish, final_path, path, nod, 0);
                start = finish;
                free(d);

                d = dijkstra(g, nod, path);
                total += d[dep];
                printf("%.1f\n", d[dep]);
                construct_path(&start, &finish, final_path, path, dep, 1);
                print_array(final_path, finish);
                free(d);
                free(final_path);

            }
            printf("%.1f", total);
            if(i != nr_task - 1) printf("\n");
        }

        if(!strcmp("e2", buffer)) {
            strongly_connected(g, e_dep);
        }

        if(!strcmp("e3", buffer)) {
            int nr_subgraf;
            scanf("%d", &nr_subgraf);
            for(int j = 0; j < nr_subgraf; j++) {
                int k;
                scanf("%d", &k);
                char *subgraf = calloc(1, g->n);
                for(int l = 0; l < k; l++){
                    int a;
                    scanf("%d", &a);
                    subgraf[a] = 1;
                }
                //pentru fiecare set, fac dijkstra modificata
                //asemenea indicatiilor din enunt
                //printez minimul pentru fiecare
                float min = modified_dijkstra(g, subgraf, e_dep);
                if(j != nr_subgraf - 1)
                    printf("%.1f\n", min);
                else printf("%.1f", min);
                free(subgraf);
            }
        }

        free(path);
    }

    free(e_dep);
    collapse_graf(g);
}