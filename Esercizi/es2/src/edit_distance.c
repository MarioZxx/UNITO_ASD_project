#include "edit_distance.h"

typedef struct _mytable{  //struct for memoization
  char **str1;
  char **str2;
  int *distance;
  int index_of_table;
}mytable;

char *rest(char *string){ //return string without first char
  string=string+1;
  return string;
}

int min_number(int first, int secnd){
  if(first<secnd) return first;
  else return secnd;
}

int edit_distance(char *string1, char *string2){  //edit_distance recursive
  if(strlen(string1)==0) return strlen(string2);
  if(strlen(string2)==0) return strlen(string1);
  if(string1[0]==string2[0] || string1[0]==string2[0]-32) 
    return edit_distance(rest(string1), rest(string2));
  return 1 + min_number( edit_distance(string1, rest(string2)),
                         edit_distance(rest(string1), string2)
                       );
}

//insert a couple of string in the table, using string as an index
void insert(char *string1, char *string2, mytable *dp_table, int dp_distance){
  int index = dp_table->index_of_table;
  dp_table->str1[index]=(char*)malloc(sizeof(char*));
  strcpy(dp_table->str1[index], string1);
  dp_table->str2[index]=(char*)malloc(sizeof(char*));
  strcpy(dp_table->str2[index], string2);
  dp_table->distance[index]=dp_distance;
  dp_table->index_of_table++;
}

//check if a couple of string exists in the table, if yes return their edit_distance
int check(char *string1, char *string2, mytable *dp_table){
    for(int i = 0; i < dp_table->index_of_table; i++){
      if(strcasecmp(dp_table->str1[i], string1)==0 && strcasecmp(dp_table->str2[i], string2)==0){
        return dp_table->distance[i];
        }
    }
  return -1;
}

//edit_distance with dynamic programming, every time calculate a distance, will be insert in the table
int edit_distance_dyn(char *string1, char *string2, mytable *dp_table){
  int dp_distance;
  if(strlen(string1)==0) return strlen(string2);
  if(strlen(string2)==0) return strlen(string1);
  dp_distance = check(string1,string2,dp_table);
  if(dp_distance!=-1) return dp_distance;
  
  if(string1[0]==string2[0] || string1[0]==string2[0]-32) {
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


int edit_distance_dyn_ric(char *string1, char *string2){  //wrapper
  mytable *dp_table = (mytable*)malloc(sizeof(mytable));
  dp_table->str1 = (char**)malloc(100000*sizeof(char*));
  dp_table->str2 = (char**)malloc(100000*sizeof(char*));
  dp_table->distance = (int*)malloc(100000*sizeof(int));
  dp_table->index_of_table = 0;
  int result = edit_distance_dyn(string1, string2, dp_table);
  
  for(int i = 0; i < dp_table->index_of_table; i++){
      free(dp_table->str1[i]);
      free(dp_table->str2[i]);
  }
  free(dp_table->str1);
  free(dp_table->str2);
  free(dp_table->distance);
  free(dp_table);
  return result;
}





