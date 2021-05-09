#include "merge_binary.h"
#define INITIAL_CAPACITY 2


SortingArray *sorting_array_create(int (*precedes)(void*, void*, short)) {
  SortingArray *sorting_array = (SortingArray*)malloc(sizeof(SortingArray));
  if (sorting_array == NULL) {
    fprintf(stderr, "sorting_array_create: unable to allocate memory for the sorting array");
    exit(EXIT_FAILURE);
  }
  sorting_array->array = (void**)malloc(INITIAL_CAPACITY * sizeof(void*));
  if (sorting_array->array == NULL) {
    fprintf(stderr, "sorting_array_create: unable to allocate memory for the internal array");
    exit(EXIT_FAILURE);
  }
  sorting_array->size = 0;
  sorting_array->array_capacity = INITIAL_CAPACITY;  
  sorting_array->precedes = precedes;
  return sorting_array;
}

void *sorting_array_get(SortingArray *sorting_array, int i) {
  if (sorting_array == NULL) {
    fprintf(stderr, "sorting_array_get: sorting_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if (i >= sorting_array->size) {
    fprintf(stderr, "sorting_array_get: Index %d is out of the array bounds", i);
    exit(EXIT_FAILURE);
  }
  return sorting_array->array[i];
}

void sorting_array_add(SortingArray *sorting_array, void *element, int index) {
  if (sorting_array == NULL) {
    fprintf(stderr, "add_sorting_array_element: sorting_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if (element == NULL) {
    fprintf(stderr, "add_sorting_array_element: element parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }

  if (sorting_array->size >= sorting_array->array_capacity) {
    sorting_array->array_capacity = 2 * sorting_array->array_capacity; // Why multiply by 2?
    sorting_array->array = (void**)realloc(sorting_array->array, sorting_array->array_capacity * sizeof(void*));
    if (sorting_array->array == NULL) {
      fprintf(stderr,"sorting_array_add: unable to reallocate memory to host the new element");
      exit(EXIT_FAILURE);
    }
  }
  sorting_array->array[index] = element;
  sorting_array->size++;
}

void sorting_array_free_memory(SortingArray *sorting_array) {
  if (sorting_array == NULL) {
    fprintf(stderr, "sorting_array_free_memory: sorting_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  free(sorting_array->array);
  free(sorting_array);
}

int sorting_array_is_empty(SortingArray *sorting_array) {
  if (sorting_array == NULL) {
    fprintf(stderr, "sorting_array_is_empty: sorting_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  return sorting_array->size == 0;
}

unsigned long sorting_array_size(SortingArray *sorting_array) {
  if (sorting_array == NULL) {
    fprintf(stderr, "sorting_array_size: sorting_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  return sorting_array->size;
}

