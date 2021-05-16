#include "edit_distance.h"
#define BUFFER_SIZE 1024
#define INITIAL_CAPACITY 2


static int load_array(const char *file_name, char **array) {
  char buffer[BUFFER_SIZE];
  
  FILE *fp;

  fp = fopen(file_name, "r");
  if (fp == NULL) {
    fprintf(stderr, "main: unable to open the file");
    exit(EXIT_FAILURE);
  }
  int index_of_array = 0;
  
  while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {

    int i=0;
    while(1){
      
      char temp[10];
      int j;
      for(j=0; isalpha(buffer[i]); j++){
        temp[j] = buffer[i];
        printf("%c- ",buffer[i]);
        i++;
      }
      temp[j]='\0';
      if(strlen(temp)!=0){
        array[index_of_array]=(char*)malloc(sizeof(temp));
        strcpy(array[index_of_array],temp);
        index_of_array++;
      }
      if(buffer[i]=='\n')break;
      else i++;
           
    }
  }
  
  fclose(fp);
  printf("there is %d words\n",index_of_array);
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
  //char **dictionary=(char**)malloc(INITIAL_CAPACITY*sizeof(char*));
  printf("\nLoading data from file...\n");
  int correct_me_size = load_array(argv[1], correct_me);
  //int dictionary_size = load_array("./dictionary.txt", dictionary);
  printf("\nData loaded\n\n");
  for(int i=0;i<correct_me_size;i++){
    printf("%s- ", correct_me[i]);
  }
  free_array(correct_me, correct_me_size);
}




