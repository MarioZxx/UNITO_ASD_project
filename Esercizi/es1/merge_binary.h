#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct _OrderArray {
  void **array;
  int size;
  int array_capacity;
  int (*precedes)(void*, void*, short, short);
}OrderArray;

OrderArray *order_array_create(int (*precedes)(void*, void*, short, short));
void order_array_add(OrderArray*, void*, int);
void *order_array_get(OrderArray*, int);
void m_bi_sort(OrderArray *order_array, int k, short field, short ascend);


