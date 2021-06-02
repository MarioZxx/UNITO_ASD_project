#include "merge_binary.h"


void merge(SortingArray *sorting_array, short ascend, int start, int mid, int end){
  int i = start, j = mid+1, k = 0; //the three index
  void **temp;
  temp=(void**)malloc(sizeof(void*)*(unsigned long)(end-start+1));
  
  while(i<=mid && j<=end){
    if(ascend==1){
      if( sorting_array->precedes(sorting_array->array[i], sorting_array->array[j]) ){
        temp[k] = sorting_array->array[i];
        i++;
      } else {
        temp[k] = sorting_array->array[j];
        j++;
      }
      k++;
    } else {
      if( !(sorting_array->precedes(sorting_array->array[i], sorting_array->array[j])) ){
        temp[k] = sorting_array->array[i];
        i++;
      } else {
        temp[k] = sorting_array->array[j];
        j++;
      }
      k++;
    }
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
  for (k=start; k<=end; k++){
    sorting_array->array[k] = temp[k-start];
    }
  free(temp);
  return;
}

void insertion_sort(SortingArray *sorting_array, short ascend, int start, int end){
  int i, j;
  void *temp;
  for (i=start+1; i <= end; i++) {
        temp = sorting_array->array[i]; //element supposed smaller
        j = i-1;
        
        if(ascend==1){
          while (j >= start && sorting_array->precedes(temp, sorting_array->array[j])) {
              sorting_array->array[j+1] = sorting_array->array[j];
              j = j - 1;
          }
        } else {
          while (j >= start && !(sorting_array->precedes(temp, sorting_array->array[j])) ) {
              sorting_array->array[j+1] = sorting_array->array[j];
              j = j - 1;
          }
        }
        
        sorting_array->array[j+1] = temp;
    }

}

void merge_sort(SortingArray *sorting_array, int k, short ascend, int start, int end){
  if(sorting_array->size == 1 || start>=end) return;
  int mid = (start+end)/2;
  if(end-start > k){
    merge_sort(sorting_array, k, ascend, start, mid);
    merge_sort(sorting_array, k, ascend, mid+1, end);
    merge(sorting_array, ascend, start, mid, end);
  } else {
    insertion_sort(sorting_array, ascend, start, end);
  }
}

/*wrapper
 *if ascend = 1 then sort in ascending, else sort in decreasing
*/
void m_bi_sort(SortingArray *sorting_array, int k, short ascend) {
if (sorting_array == NULL) {
    fprintf(stderr, "Sorting_array_is_empty: Sorting_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  merge_sort(sorting_array, k, ascend, 0, sorting_array->size-1);

}











