#include "edit_distance.h"
#define INF 1024

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

