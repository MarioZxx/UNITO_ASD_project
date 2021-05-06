#ifndef ORDER_ARRAY_H
#define ORDER_ARRAY_H



struct OrderArray {
  void **array;
  int size;
  int array_capacity;
  int (*precedes)(void*, void*, short, short);
};

OrderArray *order_array_create(int (*precedes)(void*, void*));
void order_array_add(OrderArray*, void*, int);
void *order_array_get(OrderArray*, int);
OrderArray *m_bi_sort(OrderArray *order_array, int k, short field, short ascend);

#endif // ORDER_ARRAY_H
