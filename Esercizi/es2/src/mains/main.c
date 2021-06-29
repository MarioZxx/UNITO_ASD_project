#include "../editdistance/edit_distance.h"
#define BUFFER_SIZE 1024
#define CORRECT_CAPACITY 1024
#define INITIAL_CAPACITY 2048

typedef struct _DictionaryArray {
  char **array;
  int size;
  int array_capacity;
}DictionaryArray;

DictionaryArray *dictionary_create() {
  DictionaryArray *dictionary = (DictionaryArray*)malloc(sizeof(DictionaryArray));
  if (dictionary == NULL) {
    fprintf(stderr, "dictionary_create: unable to allocate memory for the dictionary");
    exit(EXIT_FAILURE);
  }
  dictionary->array = (char**)malloc(INITIAL_CAPACITY * sizeof(char*));
  if (dictionary->array == NULL) {
    fprintf(stderr, "dictionary_create: unable to allocate memory for the dictionary array");
    exit(EXIT_FAILURE);
  }
  dictionary->size = 0;
  dictionary->array_capacity = INITIAL_CAPACITY;
  return dictionary;
}

//load correct_me file
static int load_correct_me(const char *file_name, char **array){  
  char buffer[BUFFER_SIZE];  
  FILE *fp;
  fp = fopen(file_name, "r");
  if (fp == NULL) {
    fprintf(stderr, "load_correct_me: unable to open the file correct_me\n");
    exit(EXIT_FAILURE);
  }
  int index_of_array = 0;  
  while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
    int index_line=0;
    while(1){
      char temp[27];
      int index_word=0;
      while(isalpha(buffer[index_line])){
        temp[index_word] = buffer[index_line];
        index_line++;
        index_word++;
      }
      temp[index_word]='\0';
      if(strlen(temp)!=0){
        array[index_of_array]=(char*)malloc((strlen(temp)+1)*sizeof(char));
        if (array[index_of_array] == NULL) {
          fprintf(stderr,"load_correct_me: unable to allocate memory for correct_me element");
          exit(EXIT_FAILURE);
        }
        strcpy(array[index_of_array],temp);
        index_of_array++;
      }
      if(buffer[index_line]=='\n')break;
      else index_line++;
    }
  }
  if (index_of_array == 0) {
    fprintf(stderr, "load_correct_me: there is no word in the file correct_me\n");
    exit(EXIT_FAILURE);
  }
  fclose(fp);
  printf("there are %d words in correct_me\n",index_of_array);
  return index_of_array;
}

//load dictionary file
static DictionaryArray *load_dictionary(const char *file_name, DictionaryArray *dictionary){
  char buffer[BUFFER_SIZE];
  FILE *fp;
  fp = fopen(file_name, "r");
  if (fp == NULL) {
    fprintf(stderr, "load_dictionary: unable to open the file dictionary\n");
    exit(EXIT_FAILURE);
  }
  while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
  
    if (dictionary->size >= dictionary->array_capacity) {
      dictionary->array_capacity = 2 * dictionary->array_capacity;
      dictionary->array = (char**)realloc(dictionary->array, (long unsigned int)dictionary->array_capacity * sizeof(char*));
      if (dictionary->array == NULL) {
        fprintf(stderr,"load_dictionary: unable to reallocate memory to host the new element");
        exit(EXIT_FAILURE);
      }
    }
    
    char *word_in_line = strtok(buffer, "\n");
    dictionary->array[dictionary->size]=(char*)malloc((strlen(word_in_line)+1)*sizeof(char));
      if (dictionary->array[dictionary->size] == NULL) {
        fprintf(stderr,"load_dictionary: unable to allocate memory for dictionary element");
        exit(EXIT_FAILURE);
      }
    strcpy(dictionary->array[dictionary->size], word_in_line);
    dictionary->size++;
      
  }
  if (dictionary->size == 0) {
    fprintf(stderr, "load_dictionary: there is no word in the file dictionary\n");
    exit(EXIT_FAILURE);
  }
  fclose(fp);
  printf("there are %d words in dictionary\n",dictionary->size);
  return dictionary;
}

static void free_array(char **array, int size) {
  for (int i = 0; i < size; ++i) {
    free(array[i]);
  }
  free(array);
}

//print the edit distance into a file
static void insert_list(char *string, char **list) {
  FILE *fp;
  fp = fopen("list_of_all_words.csv", "a");
  fprintf(fp,"%s : ",string);
  for (int i = 0; list[i] != NULL && i < 6; i++) {
    fprintf(fp,"%s, ",list[i]);
  }
  fwrite("\n",1,1,fp);
  fclose(fp);
}

//It should be invoked with one parameter specifying the filepath of the data file
int main(int argc, char const *argv[]) {
  if (argc < 2) {
    printf("Usage: edit_distance_main <file_name>\n");
    exit(EXIT_FAILURE);
  }
  char **correct_me=(char**)malloc(CORRECT_CAPACITY*sizeof(char*));
  if (correct_me == NULL) {
      fprintf(stderr,"main: unable to allocate memory for correct_me file");
      exit(EXIT_FAILURE);
    }
  DictionaryArray *dictionary=dictionary_create();
  
  printf("\nLoading data from file...\n");
  int correct_me_size = load_correct_me(argv[1], correct_me);
  dictionary = load_dictionary(argv[2], dictionary);
  printf("\nData loaded\n\n");
  int min, min_temp, list_index, found;
  char *min_list[1000];

  printf("Calculating...\n");
  clock_t start = clock();
  for(int i = 0; i < correct_me_size; i++){
    min = 1000;
    list_index = 0;
    found = 0;
    for(int j = 0; j < dictionary->size; j++){
      if(strcasecmp(correct_me[i], dictionary->array[j]) == 0){
        memset(min_list,0,sizeof(min_list));
        found = 1;
      }
    }
    for(int j = 0; j < dictionary->size && !found; j++){
      min_temp = edit_distance_dyn_ric(correct_me[i], dictionary->array[j]);
      if(min == min_temp){
        min_list[list_index++] = dictionary->array[j];
      }else{
        if(min > min_temp){
          min = min_temp;
          memset(min_list,0,sizeof(min_list));
          list_index = 0;
          min_list[list_index++] = dictionary->array[j];
        }
      }
    }
    insert_list(correct_me[i], min_list);
  }
  double duration = (double)(clock()-start)/CLOCKS_PER_SEC;
  printf("edit dyn time: %lf sec.\n",duration);
  
  /*start = clock();
  for(int i = 0; i < correct_me_size; i++){
    min = 100;
    list_index = 0;
    found = 0;
    for(int j = 0; j < dictionary->size; j++){
      if(strcasecmp(correct_me[i], dictionary->array[j]) == 0){
        memset(min_list,0,sizeof(min_list));
        found = 1;
      }
    }
    for(int j = 0; j < dictionary->size && !found; j++){
      min_temp = edit_distance(correct_me[i], dictionary->array[j]);
      if(min == min_temp){
        min_list[list_index++] = dictionary->array[j];
      }
      if(min>min_temp){
        min = min_temp;
        memset(min_list,0,sizeof(min_list));
        list_index = 0;
        min_list[list_index++] = dictionary->array[j];
      }
    }
    insert_list(correct_me[i], min_list);
  }
  duration = (double)(clock()-start)/CLOCKS_PER_SEC;
  printf("edit time: %lf sec.\n",duration);*/
  
  
  free_array(correct_me, correct_me_size);
  free(dictionary->array);
  free(dictionary);
}




