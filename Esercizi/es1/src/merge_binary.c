#include "merge_binary.h"


void merge(SortingArray *sorting_array, short field, short ascend, int start, int mid, int end){ //ascend = 1
  int i = start, j = mid+1, k = 0; //the three index
  //void *temp[end-start+1];
  void **temp;
  temp=(void**)malloc(sizeof(void*)*(end-start+1));
  while(i<=mid && j<=end){
    if( sorting_array->precedes(sorting_array->array[i], sorting_array->array[j], field, ascend) ){
      temp[k] = sorting_array->array[i];
      i++;
    } else {
      temp[k] = sorting_array->array[j];
      j++;
    }
    k++;
  }
  while (i <= mid) {
    temp[k] = sorting_array->array[i];
    i++;
    k++;
  }
  while (j <= end) {
    temp[k] = sorting_array->array[j];
    j++;
    k++;
  }
  for (k=start; k<=end; k++)
    sorting_array->array[k] = temp[k-start];
  free(temp);
  return;
}

void insertion_sort(SortingArray *sorting_array, short field, short ascend, int start, int end){
  int i, j;
  void *temp;
  for (i=start+1; i <= end; i++) {
        temp = sorting_array->array[i]; //value supposed smaller
        j = i-1;
        
        while (j >= start && sorting_array->precedes(temp, sorting_array->array[j], field, ascend)) {
            sorting_array->array[j+1] = sorting_array->array[j];
            j = j - 1;
        }
        sorting_array->array[j+1] = temp;
    }

}

void merge_sort(SortingArray *sorting_array, int k, short field, short ascend, int start, int end){
  if(sorting_array->size == 1 || start>=end) return;
  int mid = (start+end)/2;
  //printf("ms start: %d, mid: %d, end: %d\n", start, mid, end);
  if(end-start > k){
    merge_sort(sorting_array, k, field, ascend, start, mid);
    merge_sort(sorting_array, k, field, ascend, mid+1, end);
    merge(sorting_array, field, ascend, start, mid, end);
  } else {
    insertion_sort(sorting_array, field, ascend, start, end);
  }
}

void m_bi_sort(SortingArray *sorting_array, int k, short field, short ascend) {
if (sorting_array == NULL) {
    fprintf(stderr, "Sorting_array_is_empty: Sorting_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  merge_sort(sorting_array, k, field, ascend, 0, sorting_array->size-1);

}










