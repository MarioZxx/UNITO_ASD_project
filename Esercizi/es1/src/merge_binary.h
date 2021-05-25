#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct _SortingArray {
  void **array;
  int size;
  int array_capacity;
  int (*precedes)(void*, void*);
}SortingArray;

void m_bi_sort(SortingArray *sorting_array, int k, short ascend);
SortingArray *sorting_array_create(int (*precedes)(void*, void*));
int sorting_array_is_empty(SortingArray*);
unsigned long sorting_array_size(SortingArray*);
void sorting_array_add(SortingArray*, void*, int);
void *sorting_array_get(SortingArray*, int);
void sorting_array_free_memory(SortingArray *sorting_array);
