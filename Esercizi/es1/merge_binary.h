#ifndef ORDERED_ARRAY_H
#define ORDERED_ARRAY_H

#include <stdlib.h>
#include <stdio.h>


struct OrderedArray {
  void **array;
  unsigned long size;
  unsigned long array_capacity;
};

OrderedArray *ordered_array_create();
void ordered_array_add(OrderedArray*, void*, unsigned long);
void *ordered_array_get(OrderedArray*, unsigned long);

#endif // ORDERED_ARRAY_H
