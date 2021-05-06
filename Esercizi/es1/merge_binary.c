#include <stdlib.h>
#include <stdio.h>
#include "merge_binary.h"

OrderArray *m_bi_sort(OrderArray *order_array, int k, short field, short ascend) {
if (ordered_array == NULL) {
    fprintf(stderr, "ordered_array_is_empty: ordered_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  return merge_sort(order_array, k, field, ascend, 0, order_array->size);

}

void merge_sort(OrderArray *order_array, int k, short field, short ascend, int start, int end){
  if(order_array->size = 1) return order_array;
  int mid = (start+end)/2;
  if(mid > k){
    merge_sort(order_array, k, field, ascend, start, mid);
    merge_sort(order_array, k, field, ascend, mid+1, end);
    merge(order_array, k, field, ascend, start, mid, end);
  } else {
    insertion_sort(order_array, k, field, ascend);
  }
}

void merge(OrderArray *order_array, int k, short field, short ascend, int start, int mid, int end){ //ascend = 1
  int i = start, j = mid+1, k = 0; //the three index
  void *temp[end-start+1];
  
  while(i<=start && j<=end){
    if( order_array->precedes(order_array->array[i], order_array->array[j], field, ascend) ){
      temp[k] = order_array->array[i];
      i++;
    } else {
      temp[k] = order_array->array[j];
      j++;
    }
    k++;
  }
  while (i <= mid) {
    temp[k] = order_array->array[i];
    i++;
    k++;
  }
  while (j <= end) {
    temp[k] = order_array->array[j];
    j++;
    k++;
  }
  for (k=start; k<=end; k++)
    order_array->array[k] = temp[k-start];
    
  return;
}

void insertion_sort(OrderArray *order_array, int k, short field, short ascend){


}











