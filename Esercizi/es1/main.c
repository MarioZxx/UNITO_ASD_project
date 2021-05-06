#include "merge_binary.h"

typedef struct _record {
  int int_id;
  char *string_field;
  int integer_field;
  float float_field;
} Record;

static void load_array(const char *file_name, OrderedArray *array) {
  char buffer[BUFFER_SIZE];
  FILE *fp;

  printf("\nLoading data from file...\n");
  fp = fopen(file_name, "r");
  if (fp == NULL) {
    fprintf(stderr, "main: unable to open the file");
    exit(EXIT_FAILURE);
  }

  while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
    unsigned long index_of_array = 0;
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
    ordered_array_add(array, (void*)record_p,index_of_array);
    index_of_array++;
  }
  fclose(fp);
  printf("\nData loaded\n");
}

static void get_array(OrderedArray *ordered_array) {
  unsigned long size = array->size;
  FILE *fp;
  fp = fopen("output_file.csv", "w");
  printf("\nStart output...\n");
  for (unsigned long i = 0; i < size; ++i) {
    Record *array_element = (Record*)ordered_array_get(ordered_array, i);
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

static void free_array(OrderedArray *ordered_array) {
  unsigned long size = array->size;
  for (unsigned long i = 0; i < size; ++i) {
    Record *array_element = (Record*)ordered_array_get(ordered_array, i);
    free(array_element->string_field);
    free(array_element);
  }
  free(ordered_array->array);
  free(ordered_array);
}

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    printf("Usage: ordered_array_main <file_name>\n");
    exit(EXIT_FAILURE);
  }
  OrderedArray *array = ordered_array_create();
  load_array(argv[1], array);
  
  /*fscanf k and mode*/
  //m_bi_sort(array, k, mode);
  
  get_array(array);
  free(array);
  return EXIT_SUCCESS;
}


