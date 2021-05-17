#include "edit_distance.h"

typedef struct _mytable{
  char **str1;
  char **str2;
  int *distance;
  int index_of_table;
}mytable;

char *rest(char *string){
  string=string+1;
  return string;
}

int min_number(int first, int secnd, int third){
  int min;
  if(first<secnd) min=first;
  else min=secnd;
  if(min<third) return min;
  else return third;
}

int edit_distance(char *string1, char *string2){
  if(strlen(string1)==0) return strlen(string2);
  if(strlen(string2)==0) return strlen(string1);
  if(string1[0]==string2[0]) return edit_distance(rest(string1), rest(string2));
  return 1 + min_number( edit_distance(string1, rest(string2)),
                         edit_distance(rest(string1), string2),
                         10 + edit_distance(rest(string1), rest(string2))
                       );
}

void insert(char *string1, char *string2, mytable *dp_table, int dp_distance){
  int index = dp_table->index_of_table;
  dp_table->str1[index]=(char*)malloc(sizeof(char*));
  strcpy(dp_table->str1[index], string1);
  dp_table->str2[index]=(char*)malloc(sizeof(char*));
  strcpy(dp_table->str2[index], string2);
  dp_table->distance[index]=dp_distance;
  dp_table->index_of_table++;
};

int check(char *string1, char *string2, mytable *dp_table){
    for(int i = 0; i<dp_table->index_of_table; i++){
      if(dp_table->str1[i]==string1 && dp_table->str2[i]==string2)
        return dp_table->distance[i];
    }
  return 0;
}

int edit_distance_dyn(char *string1, char *string2, mytable *dp_table){
  int dp_distance;
  if(strlen(string1)==0) return strlen(string2);
  if(strlen(string2)==0) return strlen(string1);
  if(dp_distance=check(string1,string2,dp_table)) return dp_distance;
  
  if(string1[0]==string2[0]) {
    //printf("equal, %c, %c\n",string1[0],string2[0]);
    dp_distance = edit_distance_dyn(rest(string1), rest(string2), dp_table);
    insert(string1, string2, dp_table, dp_distance);
    return dp_distance;
  }
  dp_distance = 1 + min_number( edit_distance_dyn(string1, rest(string2), dp_table),
                         edit_distance_dyn(rest(string1), string2, dp_table),
                         10 + edit_distance_dyn(rest(string1), rest(string2), dp_table)
                       );
  insert(string1, string2, dp_table, dp_distance);
  return dp_distance;
}


int edit_distance_dyn_ric(char *string1, char *string2){
  int slen1=strlen(string1);
  int slen2=strlen(string2);
  mytable *dp_table = (mytable*)malloc(sizeof(mytable));
  dp_table->str1 = (char**)malloc(10000*sizeof(char*));
  dp_table->str2 = (char**)malloc(10000*sizeof(char*));
  dp_table->distance = (int*)malloc(10000*sizeof(int));
  dp_table->index_of_table = 0;
  int result = edit_distance_dyn(string1, string2, dp_table);
  for(int i = 0; i<dp_table->index_of_table; i++){
      free(dp_table->str1[i]);
      free(dp_table->str2[i]);
  }
  free(dp_table->str1);
  free(dp_table->str2);
  free(dp_table->distance);
  free(dp_table);
  return result;
}





