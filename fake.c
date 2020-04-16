#include <stdio.h>
#include <string.h>

int main(){
  char s[255];
  int i;
  FILE* f1 = fopen("anhviet.txt", "r");
  FILE* f2 = fopen("fake.txt", "w");
  fgets(s, 255, f1);
  for(i = 0; s[i]!= '@'; i++) printf("%c", s[i]);
  fprintf(f2, "%s", s + i);
  while(!feof(f1)){
    fgets(s, 255, f1);
    if(s[0] == '^') break;
    fprintf(f2, "%s", s);
  }
  fclose(f1);
  fclose(f2);
  return 0;
}
