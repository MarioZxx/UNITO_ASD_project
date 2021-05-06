#include "merge_binary.h"
#define INITIAL_CAPACITY 2


OrderedArray *ordered_array_create() {
  OrderedArray *ordered_array = (OrderedArray*)malloc(sizeof(OrderedArray));
  if (ordered_array == NULL) {
    fprintf(stderr, "ordered_array_create: unable to allocate memory for the ordered array");
    exit(EXIT_FAILURE);
  }
  ordered_array->array = (void**)malloc(INITIAL_CAPACITY * sizeof(void*));
  if (ordered_array->array == NULL) {
    fprintf(stderr, "ordered_array_create: unable to allocate memory for the internal array");
    exit(EXIT_FAILURE);
  }
  ordered_array->size = 0;
  ordered_array->array_capacity = INITIAL_CAPACITY;
  return ordered_array;
}

void *ordered_array_get(OrderedArray *ordered_array, unsigned long i) {
  if (ordered_array == NULL) {
    fprintf(stderr, "ordered_array_get: ordered_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if (i >= ordered_array->size) {
    fprintf(stderr, "ordered_array_get: Index %lu is out of the array bounds", i);
    exit(EXIT_FAILURE);
  }
  return ordered_array->array[i];
}

void ordered_array_add(OrderedArray *ordered_array, void *element, unsigned long index) {
  if (ordered_array == NULL) {
    fprintf(stderr, "add_ordered_array_element: ordered_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if (element == NULL) {
    fprintf(stderr, "add_ordered_array_element: element parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }

  if (ordered_array->size >= ordered_array->array_capacity) {
    ordered_array->array_capacity = 2 * ordered_array->array_capacity; // Why multiply by 2?
    ordered_array->array = (void**)realloc(ordered_array->array, ordered_array->array_capacity * sizeof(void*));
    if (ordered_array->array == NULL) {
      fprintf(stderr,"ordered_array_add: unable to reallocate memory to host the new element");
      exit(EXIT_FAILURE);
    }
  }
  ordered_array->array[index] = element;
  ordered_array->size++;
}

