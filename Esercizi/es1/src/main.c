#include "merge_binary.h"
#define BUFFER_SIZE 1024

typedef struct _record {
  int int_id;
  char *string_field;
  int integer_field;
  double double_field;
} Record;

static int precedes_record_string(void *r1_p, void *r2_p) {
  if (r1_p == NULL) {
    fprintf(stderr, "precedes_record: the first parameter is a null pointer\n");
    exit(EXIT_FAILURE);
  }
  if (r2_p == NULL) {
    fprintf(stderr, "precedes_record: the second parameter is a null pointer\n");
    exit(EXIT_FAILURE);
  }
  Record *rec1_p = (Record*)r1_p;
  Record *rec2_p = (Record*)r2_p;    
  return strcmp(rec1_p->string_field, rec2_p->string_field) < 0;
}

static int precedes_record_integer(void *r1_p, void *r2_p) {
  if (r1_p == NULL) {
    fprintf(stderr, "precedes_record: the first parameter is a null pointer\n");
    exit(EXIT_FAILURE);
  }
  if (r2_p == NULL) {
    fprintf(stderr, "precedes_record: the second parameter is a null pointer\n");
    exit(EXIT_FAILURE);
  }
  Record *rec1_p = (Record*)r1_p;
  Record *rec2_p = (Record*)r2_p;
  return rec1_p->integer_field < rec2_p->integer_field;
}

static int precedes_record_double(void *r1_p, void *r2_p) {
  if (r1_p == NULL) {
    fprintf(stderr, "precedes_record: the first parameter is a null pointer\n");
    exit(EXIT_FAILURE);
  }
  if (r2_p == NULL) {
    fprintf(stderr, "precedes_record: the second parameter is a null pointer\n");
    exit(EXIT_FAILURE);
  }
  Record *rec1_p = (Record*)r1_p;
  Record *rec2_p = (Record*)r2_p;
  return rec1_p->double_field < rec2_p->double_field;
}


static void load_array(const char *file_name, SortingArray *array) {
  char buffer[BUFFER_SIZE];
  FILE *fp;

  printf("\nLoading data from file...\n");
  fp = fopen(file_name, "r");
  if (fp == NULL) {
    fprintf(stderr, "main: unable to open the file");
    exit(EXIT_FAILURE);
  }

  int index_of_array = 0;
  while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
    Record *record_p = malloc(sizeof(Record));
    if (record_p == NULL) {
      fprintf(stderr,"main: unable to allocate memory for the read record");
      exit(EXIT_FAILURE);
    }
    char *int_id_in_read_line_p = strtok(buffer, ",");
    char *string_field_in_read_line_p = strtok(NULL, ",");
    char *integer_field_in_read_line_p = strtok(NULL, ",");
    char *double_field_in_read_line_p = strtok(NULL, "\n");
    
    record_p->int_id = atoi(int_id_in_read_line_p);
    record_p->string_field = malloc((strlen(string_field_in_read_line_p)+1) * sizeof(char));
    if (record_p->string_field == NULL) {
      fprintf(stderr,"main: unable to allocate memory for the string field of the read record");
      exit(EXIT_FAILURE);
    }
    strcpy(record_p->string_field, string_field_in_read_line_p);
    record_p->integer_field = atoi(integer_field_in_read_line_p);
    record_p->double_field = atof(double_field_in_read_line_p);
    sorting_array_add(array, (void*)record_p, index_of_array);
    index_of_array++;
  }
    printf("array size: %d\n",array->size);
  fclose(fp);
  printf("Data loaded\n");
}

static void get_array(SortingArray *sorting_array) {  //creats output file in csv with array ordered
  int size = sorting_array->size;
  FILE *fp;
  fp = fopen("output_file.csv", "w");
  printf("\nStart output...\n");
  for (int i = 0; i < size; ++i) {
    Record *array_element = (Record*)sorting_array_get(sorting_array, i);
    fprintf(fp,"%d",array_element->int_id);
    fwrite(",",1,1,fp);
    fprintf(fp,"%s",array_element->string_field);
    fwrite(",",1,1,fp);
    fprintf(fp,"%d",array_element->integer_field);
    fwrite(",",1,1,fp);
    fprintf(fp,"%.6f",array_element->double_field);
    fwrite("\n",1,1,fp);
  }
  fclose(fp);
  printf("Output with success.\n");
}

static void free_array(SortingArray *sorting_array) {
  int size = sorting_array->size;
  for (int i = 0; i < size; ++i) {
    Record *array_element = (Record*)sorting_array_get(sorting_array, i);
    free(array_element->string_field);
    free(array_element);
  }
  free(sorting_array->array);
  free(sorting_array);
}

static void test_with_comparison_function(const char *file_name, int (*compare)(void*, void*),
int k, short ascend, char *field) {
  SortingArray *array = sorting_array_create(compare);
  load_array(file_name, array);
  
  clock_t start = clock();
  m_bi_sort(array, k, ascend);
  double duration =  (double)(clock() - start)/CLOCKS_PER_SEC;  
  printf("The duration of the %s field m_bi_sort is %f sec. \n", field, duration);
  
  printf("Do you want the output file?[y/n]\n");
  char res=(char)getchar();getchar();
  if(res=='y')
    { get_array(array); }
  
  free_array(array);
}

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    printf("Usage: sorting_array_main <file_name>\n");
    exit(EXIT_FAILURE);
  }
  char *field;
  int k;
  short ascend=1;
  
  printf("Insert the value of k\n");
  while(scanf("%d",&k) < 0)
    printf("Please insert a value of k");
  getchar();
  printf("Do you want sort in ascending order?[y/n]\n");
  char res=(char)getchar();getchar();
  if(res=='y') {
    ascend=1;
  }else{ 
    ascend=0;}
  
  printf("Sorting...\n");
  field = "string";
  test_with_comparison_function(argv[1], precedes_record_string, k, ascend, field);
  field = "integer";
  test_with_comparison_function(argv[1], precedes_record_integer, k, ascend, field);
  field = "double";
  test_with_comparison_function(argv[1], precedes_record_double, k, ascend, field);
  printf("\nFinished. \n");
  
  return EXIT_SUCCESS;
}


