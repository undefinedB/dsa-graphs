#ifndef __graf__
#define __graf__

typedef struct node{
    int nod;
    float cost;  
    struct node *next;
} node;

typedef struct graf{
    int n;//nr de noduri
    node **adj;
} graf;

node *new_list(int nod, float cost);
void free_list(node **l);
void add_node(node **l, int nod, float cost);
graf *create_graf(int nodes);
void add_edge(graf *g, int nod1, int nod2, float cost);
void print_graf(graf *g);
void collapse_graf(graf *g);
void construct_path(int *start, int *finish, int *final_path, int *dijkstra_path, int nodstart, int ignore_last_node);
void invert_array(int *path, int start, int finish);
void strongly_connected(graf *g, char *e_dep);
void dfs(graf *g, char *viz, int comp, int *v, int current, char *e_dep);
int is_connected(graf *g, int nod1, int nod2, char *e_dep);


#endif