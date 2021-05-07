#include "merge_binary.h"
#define INITIAL_CAPACITY 2


OrderArray *order_array_create(int (*precedes)(void*, void*, short, short)) {
  OrderArray *order_array = (OrderArray*)malloc(sizeof(OrderArray));
  if (order_array == NULL) {
    fprintf(stderr, "order_array_create: unable to allocate memory for the order array");
    exit(EXIT_FAILURE);
  }
  order_array->array = (void**)malloc(INITIAL_CAPACITY * sizeof(void*));
  if (order_array->array == NULL) {
    fprintf(stderr, "order_array_create: unable to allocate memory for the internal array");
    exit(EXIT_FAILURE);
  }
  order_array->size = 0;
  order_array->array_capacity = INITIAL_CAPACITY;  
  order_array->precedes = precedes;
  return order_array;
}

void *order_array_get(OrderArray *order_array, int i) {
  if (order_array == NULL) {
    fprintf(stderr, "order_array_get: order_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if (i >= order_array->size) {
    fprintf(stderr, "order_array_get: Index %d is out of the array bounds", i);
    exit(EXIT_FAILURE);
  }
  return order_array->array[i];
}

void order_array_add(OrderArray *order_array, void *element, int index) {
  if (order_array == NULL) {
    fprintf(stderr, "add_order_array_element: order_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if (element == NULL) {
    fprintf(stderr, "add_order_array_element: element parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }

  if (order_array->size >= order_array->array_capacity) {
    order_array->array_capacity = 2 * order_array->array_capacity; // Why multiply by 2?
    order_array->array = (void**)realloc(order_array->array, order_array->array_capacity * sizeof(void*));
    if (order_array->array == NULL) {
      fprintf(stderr,"order_array_add: unable to reallocate memory to host the new element");
      exit(EXIT_FAILURE);
    }
  }
  order_array->array[index] = element;
  order_array->size++;
}

