#ifndef __heap__
#define __heap__

//pentru ca structura de heap normala nu este suficienta pentru dijkstra,
//am implementat un heap ce retine si pozitia fiecarui element din heap,
//prin map
typedef struct binary_heap{
    int n;//nr maxim de elemente
    int curr;//numar curent de elemente
    int *heap;
    int *map;
} binary_heap;

void swap(int *a, int *b);
int parent(int i);
int left(int i);
int right(int i);
binary_heap *create_heap(int max);
void add_to_binary_heap(binary_heap *h, int x, float *d);
int remove_from_binary_heap(binary_heap *h, float *d);
void print_array(int *array, int n);
void increase_priority(binary_heap *h, int x, float *d);

#endif
