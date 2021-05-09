#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct _SortingArray {
  void **array;
  int size;
  int array_capacity;
  int (*precedes)(void*, void*, short, short);
}SortingArray;

SortingArray *sorting_array_create(int (*precedes)(void*, void*, short, short));
void sorting_array_add(SortingArray*, void*, int);
void *sorting_array_get(SortingArray*, int);
void m_bi_sort(SortingArray *sorting_array, int k, short field, short ascend);
