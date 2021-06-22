#include "edit_distance.h"

//struct for memoization
typedef struct _mytable{
  int *distanceArray;
  int rowLength;
}mytable;

//return string without first char
char *rest(char *string){ 
  string=string+1;
  return string;
}

int min_number(int first, int secnd){
  if(first<secnd) return first;
  else return secnd;
}

//edit_distance recursive version
int edit_distance(char *string1, char *string2){
  if(strlen(string1)==0) return (int)strlen(string2);
  if(strlen(string2)==0) return (int)strlen(string1);
  if(string1[0]==string2[0] || string1[0]==string2[0]-32 || string1[0]==string2[0]+32) 
    return edit_distance(rest(string1), rest(string2));
  return 1 + min_number( edit_distance(string1, rest(string2)),
                         edit_distance(rest(string1), string2)
                       );
}

//insert a couple of string in the table, using string as an index
void insert(char *string1, char *string2, mytable *dp_table, int dp_distance){
  dp_table->distanceArray[(int)strlen(string1) * dp_table->rowLength + (int)strlen(string2)] = dp_distance;
}

//check if a couple of string exists in the table, if yes return their edit_distance
int check(char *string1, char *string2, mytable *dp_table){
  if(dp_table->distanceArray[(int)strlen(string1) * dp_table->rowLength + (int)strlen(string2)] != -1)
    return dp_table->distanceArray[(int)strlen(string1) * dp_table->rowLength + (int)strlen(string2)];
  return -1;
}

//edit_distance with dynamic programming, every time calculate a distance, will be insert in the table
int edit_distance_dyn(char *string1, char *string2, mytable *dp_table){
  int dp_distance;
  if(strlen(string1)==0) return (int)strlen(string2);
  if(strlen(string2)==0) return (int)strlen(string1);
  dp_distance = check(string1,string2,dp_table);
  if(dp_distance!=-1) return dp_distance;
  
  if(string1[0]==string2[0] || string1[0]==string2[0]-32 || string1[0]==string2[0]+32) {
    dp_distance = edit_distance_dyn(rest(string1), rest(string2), dp_table);
    insert(string1, string2, dp_table, dp_distance);
    return dp_distance;
  }
  dp_distance = 1 + min_number( edit_distance_dyn(string1, rest(string2), dp_table),
                                edit_distance_dyn(rest(string1), string2, dp_table)
                              );
  insert(string1, string2, dp_table, dp_distance);
  return dp_distance;
}

//wrapper, it needs two input string
int edit_distance_dyn_ric(char *string1, char *string2){
  if(strcasecmp(string1, string2) == 0){
        return 0;
  }
  mytable *dp_table = (mytable*)malloc(sizeof(mytable));
  if (dp_table == NULL) {
    fprintf(stderr,"edit_distance_dyn_ric: unable to allocate memory for dp_table");
    exit(EXIT_FAILURE);
  }
  dp_table->distanceArray = (int*)malloc((strlen(string1)+1) * (strlen(string2)+1) * sizeof(int));
  if (dp_table->distanceArray == NULL) {
      fprintf(stderr,"edit_distance_dyn_ric: unable to allocate memory for internal arrays");
      exit(EXIT_FAILURE);
  }
  memset(dp_table->distanceArray, -1, ((strlen(string1)+1) * (strlen(string2)+1) * sizeof(int)) );
  dp_table->rowLength = (int)strlen(string2) + 1;
  int result = edit_distance_dyn(string1, string2, dp_table);
  
  free(dp_table->distanceArray);
  free(dp_table);
  return result;
}





