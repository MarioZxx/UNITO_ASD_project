#include "edit_distance.h"
#define BUFFER_SIZE 1024
#define INITIAL_CAPACITY 1024


static int load_correct_me(const char *file_name, char **array) {
  char buffer[BUFFER_SIZE];  
  FILE *fp;
  fp = fopen(file_name, "r");
  if (fp == NULL) {
    fprintf(stderr, "main: unable to open the file correct_me");
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
  fclose(fp);
  printf("there is %d words\n",index_of_array);
  return index_of_array;
}

static int load_dictionary(const char *file_name, char **array) {
  char buffer[BUFFER_SIZE];  
  FILE *fp;
  fp = fopen(file_name, "r");
  if (fp == NULL) {
    fprintf(stderr, "main: unable to open the file dictionary");
    exit(EXIT_FAILURE);
  }
  int index_of_array = 0;  
  while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
    
    char *word_in_line = strtok(buffer, "\n");
    array[index_of_array]=(char*)malloc(sizeof(word_in_line));
    strcpy(array[index_of_array], word_in_line);
    index_of_array++;
      
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
  
  
  
  free_array(dictionary, dictionary_size);
  free_array(correct_me, correct_me_size);
}




