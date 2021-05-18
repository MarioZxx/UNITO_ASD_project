#include "edit_distance.h"
#define BUFFER_SIZE 1024
#define INITIAL_CAPACITY 1024


static int load_correct_me(const char *file_name, char **array){  //load correct_me file
  char buffer[BUFFER_SIZE];  
  FILE *fp;
  fp = fopen(file_name, "r");
  if (fp == NULL) {
    fprintf(stderr, "main: unable to open the file correct_me\n");
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
        array[index_of_array]=(char*)malloc(sizeof(temp));
        strcpy(array[index_of_array],temp);
        index_of_array++;
      }
      if(buffer[index_line]=='\n')break;
      else index_line++;
    }
  }
  if (index_of_array == 0) {
    fprintf(stderr, "main: there is no word in the file correct_me\n");
    exit(EXIT_FAILURE);
  }
  fclose(fp);
  printf("there are %d words\n",index_of_array);
  return index_of_array;
}

static int load_dictionary(const char *file_name, char **array){  //load dictionary file
  char buffer[BUFFER_SIZE];  
  FILE *fp;
  fp = fopen(file_name, "r");
  if (fp == NULL) {
    fprintf(stderr, "main: unable to open the file dictionary\n");
    exit(EXIT_FAILURE);
  }
  int index_of_array = 0;  
  while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
    
    char *word_in_line = strtok(buffer, "\n");
    array[index_of_array]=(char*)malloc(sizeof(word_in_line));
    strcpy(array[index_of_array], word_in_line);
    index_of_array++;
      
  }
  if (index_of_array == 0) {
    fprintf(stderr, "main: there is no word in the file correct_me\n");
    exit(EXIT_FAILURE);
  }
  fclose(fp);
  return index_of_array;
}

static void free_array(char **array, int size) {
  for (int i = 0; i < size; ++i) {
    free(array[i]);
  }
  free(array);
}

static void insert_list(char *string, char **list) {  //creats output file in csv with array ordered
  FILE *fp;
  fp = fopen("list_of_all_words.csv", "a");
  fprintf(fp,"%s : ",string);
  for (int i = 0; list[i] != NULL; i++) {
    fprintf(fp,"%s, ",list[i]);
  }
  fwrite("\n",1,1,fp);
  fclose(fp);
}

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    printf("Usage: edit_distance_main <file_name>\n");
    exit(EXIT_FAILURE);
  }
  char **correct_me=(char**)malloc(INITIAL_CAPACITY*sizeof(char*));
  char **dictionary=(char**)malloc(1000000*sizeof(char*));
  printf("\nLoading data from file...\n");
  int correct_me_size = load_correct_me(argv[1], correct_me);
  int dictionary_size = load_dictionary("./dictionary.txt", dictionary);
  printf("\nData loaded\n\n");
  int min, min_temp, list_index;
  char *min_list[100];
  
  printf("Calculating...\n");
  clock_t start = clock();
  for(int i = 0; i < correct_me_size; i++){
    min = 100;
    list_index = 0;
    for(int j = 0; j < dictionary_size; j++){
      min_temp = edit_distance_dyn_ric(correct_me[i], dictionary[j]);
      if(min == min_temp){
        min_list[list_index++] = dictionary[j];
      }
      if(min>min_temp){
        min=min_temp;
        memset(min_list,0,sizeof(min_list));
        list_index = 0;
        min_list[list_index++] = dictionary[j];
      }
      
      
    }
    insert_list(correct_me[i], min_list);
  }
  double duration = (double)(clock()-start)/CLOCKS_PER_SEC;
  printf("edit dyn time: %lf\n",duration);
  
  start = clock();
  for(int i = 0; i < correct_me_size; i++){
    min = 100;
    list_index = 0;
    for(int j = 0; j < dictionary_size; j++){
      min_temp = edit_distance(correct_me[i], dictionary[j]);
      if(min == min_temp){
        min_list[list_index++] = dictionary[j];
      }
      if(min>min_temp){
        min=min_temp;
        memset(min_list,0,sizeof(min_list));
        list_index = 0;
        min_list[list_index++] = dictionary[j];
      }
      
      
    }
    insert_list(correct_me[i], min_list);
  }
  duration = (double)(clock()-start)/CLOCKS_PER_SEC;
  printf("edit time: %lf se.\n",duration);
  
  
  free_array(dictionary, dictionary_size);
  free_array(correct_me, correct_me_size);
  
}




