#include <stdlib.h>
#include <stdio.h>
#include "merge_binary.h"

typedef struct _record {
  int int_id;
  char *string_field;
  int integer_field;
  float float_field;
} Record;

static int precedes_record(void *r1_p, void *r2_p, short field, short ascend) {  //if i want order int/float field = 2/3, for string field = 1
  if (r1_p == NULL) {
    fprintf(stderr, "precedes_record_int_field: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if (r2_p == NULL) {
    fprintf(stderr, "precedes_record_int_field: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  Record *rec1_p = (Record*)r1_p;
  Record *rec2_p = (Record*)r2_p;
  
  if(ascend){
    switch(field){
      case 1: return strcmp(rec1_p->string_field, rec2_p->string_field) < 0;
      case 2: return rec1_p->integer_field < rec2_p->integer_field;
      case 3: return rec1_p->float_field < rec2_p->float_field;
      default:  fprintf(stderr, "precedes_record: the field type is wrong");
                exit(EXIT_FAILURE);
    }
  } else {
    switch(field){
      case 1: return strcmp(rec1_p->string_field, rec2_p->string_field) > 0;
      case 2: return rec1_p->integer_field > rec2_p->integer_field;
      case 3: return rec1_p->float_field > rec2_p->float_field;
      default:  fprintf(stderr, "precedes_record: the field type is wrong");
                exit(EXIT_FAILURE);
    }
  }
}


static void load_array(const char *file_name, OrderArray *array) {
  char buffer[BUFFER_SIZE];
  FILE *fp;

  printf("\nLoading data from file...\n");
  fp = fopen(file_name, "r");
  if (fp == NULL) {
    fprintf(stderr, "main: unable to open the file");
    exit(EXIT_FAILURE);
  }

  while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
    int index_of_array = 0;
    Record *record_p = malloc(sizeof(Record));
    if (record_p == NULL) {
      fprintf(stderr,"main: unable to allocate memory for the read record");
      exit(EXIT_FAILURE);
    }
    
    char *int_id_in_read_line_p = strtok(NULL, ",");
    char *string_field_in_read_line_p = strtok(buffer, ",");
    char *integer_field_in_read_line_p = strtok(NULL, ",");
    char *float_field_in_read_line_p = strtok(NULL, ",");
    
    record_p->int_id = atoi(int_id_in_read_line_p);
    record_p->string_field = malloc((strlen(string_field_in_read_line_p)+1) * sizeof(char));
    if (record_p->string_field == NULL) {
      fprintf(stderr,"main: unable to allocate memory for the string field of the read record");
      exit(EXIT_FAILURE);
    }
    strcpy(record_p->string_field, string_field_in_read_line_p);
    record_p->integer_field = atoi(integer_field_in_read_line_p);
    record_p->float_field = atof(float_field_in_read_line_p);
    order_array_add(array, (void*)record_p, index_of_array);
    index_of_array++;
  }
  fclose(fp);
  printf("\nData loaded\n");
}

static void get_array(OrderArray *order_array) {  //creats output file in csv with array ordered
  int size = array->size;
  FILE *fp;
  fp = fopen("output_file.csv", "w");
  printf("\nStart output...\n");
  for (int i = 0; i < size; ++i) {
    Record *array_element = (Record*)order_array_get(order_array, i);
    fwrite(array_element->int_id,1,strlen(array_element->int_id),fp);
    fwrite(",",1,1,fp);
    fwrite(array_element->string_field,1,strlen(array_element->string_field),fp);
    fwrite(",",1,1,fp);
    fwrite(array_element->int_field,1,strlen(array_element->int_field),fp);
    fwrite(",",1,1,fp);
    fwrite(array_element->float_field,1,strlen(array_element->float_field),fp);
    fwrite("\n",1,1,fp);
  }
  fclose(fp);
  printf("\nOutput with success.\n");
}

static void free_array(OrderArray *order_array) {
  int size = array->size;
  for (int i = 0; i < size; ++i) {
    Record *array_element = (Record*)order_array_get(order_array, i);
    free(array_element->string_field);
    free(array_element);
  }
  free(order_array->array);
  free(order_array);
}

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    printf("Usage: order_array_main <file_name>\n");
    exit(EXIT_FAILURE);
  }
  char res;
  int k, 
  short field, ascend;
  double duration;
  clock_t start,stop;
  
  OrderArray *array = order_array_create(precedes_record);
  OrderArray *new_array = order_array_create(precedes_record);
  load_array(argv[1], array);
  printf("Insert the value of k");
  scanf("%d",&k);
  printf("Choose between field1 string, field2 int, field3 float [1/2/3]");//devo ancora applicare il controllo su inserimento
  scanf("%d",&field);
  printf("Do want order in ascending order?[y/n]")
  if(getchar()=='y') 
    ascend=1;
  else 
    ascend=0;
    
  start = clock();
  new_array = m_bi_sort(array, k, field, ascend);
  stop=clock();
  duration =  (double)(stop-start);
  
  printf("The duration of the m_bi_sort is %f. \n",duration);
  printf("Do you want the output file?[y/n]");
  res=getchar();
  if(res=='y')
    { get_array(array); }
  
  free(array);
  return EXIT_SUCCESS;
}


