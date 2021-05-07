#include "merge_binary.h"

void merge(OrderArray *order_array, short field, short ascend, int start, int mid, int end){ //ascend = 1
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

void insertion_sort(OrderArray *order_array, short field, short ascend){
  int i, j;
  void *temp;
  for (i=1; i < (order_array->size); i++) {
        temp = order_array->array[i]; //value supposed smaller
        j = i-1;
        
        printf("is index i: %d\n",i);
        while (j >= 0 && order_array->precedes(temp, order_array->array[j], field, ascend)) {
            order_array->array[j+1] = order_array->array[j];
            j = j - 1;
        }
        order_array->array[j+1] = temp;
    }

}

void merge_sort(OrderArray *order_array, int k, short field, short ascend, int start, int end){
  if(order_array->size == 1 || start>=end) return;
  int mid = (start+end)/2;
  printf("ms start: %d, mid: %d, end: %d\n", start, mid, end);
  if(end-start > k){
    merge_sort(order_array, k, field, ascend, start, mid);
    merge_sort(order_array, k, field, ascend, mid+1, end);
    merge(order_array, field, ascend, start, mid, end);
  } else {
    insertion_sort(order_array, field, ascend);
  }
}

void m_bi_sort(OrderArray *order_array, int k, short field, short ascend) {
if (order_array == NULL) {
    fprintf(stderr, "ordered_array_is_empty: ordered_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  merge_sort(order_array, k, field, ascend, 0, order_array->size-1);

}











