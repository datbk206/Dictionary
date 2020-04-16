#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "btree.h"
#define MAX 20000
char dem[10];
void soundex(char *sdex, char *s){
  char copy[4] = "aaaa";
  int i;
  copy[0] = s[0];
  sdex[0] = copy[0];
  for(i = 1; i < 4; i++){
    if(s[i] >= 'a' && s[i] <= 'z') copy[i] = s[i];
    switch(copy[i]){
    case 'b':
    case 'f':
    case 'p':
    case 'v':
      sdex[i] = '1'; break;
    case 'c':
    case 'g':
    case 'j':
    case 'k':
    case 'q':
    case 's':
    case 'x':
    case 'z':
      sdex[i] = '2'; break;
    case 'd':
    case 't':
      sdex[i] = '3'; break;
    case 'l':
      sdex[i] = '4'; break;
    case 'm':
    case 'n':
      sdex[i] = '5'; break;
    case 'r':
      sdex[i] = '6'; break;
    default:
      sdex[i] = '0'; break;  
    }
  }
  sdex[4] = 0;
  printf("%s\n", sdex);
}

void tachtu(char * s, char * tu, char * phatam){
  int i, j;
  for(i = 0; s[i]!= 47; i++)
    tu[i] = s[i];
  tu[i - 1] = 0;
  for(j = i; s[j]; j++)
    phatam[j - i] = s[j];
  phatam[j - i] = 0;
 
}

void addd(char* nghia, char* dong){
  int i = strlen(nghia), j = 0;
  for(j = 0; j < strlen(dong); j++)
    nghia[i + j] = dong[j];
  nghia[i + j] = 0;
}
//
void btree(BTA **root){
  *root = btopn("data", 0 ,0);
  if(!(*root)){
    FILE *f;
    f=fopen("fake.txt","r");
    *root = btcrt("data", 0, 0);
    char word[20], translate[MAX], tmp[100];
    
    translate[0] = 0;
    while(!feof(f)){
      fgets(tmp, 100, f);
      while(tmp[0] != '@'){
	addd(translate, tmp);
	if(feof(f)) break;
	fgets(tmp, 100, f);
	
      }
      
      int k = btins(*root, word, translate,(strlen(translate)+ 1)*sizeof(char));
      if(tmp[0] == '@'){
	tachtu(tmp + 1, word, translate);
      }
      
    }
    fclose(f);
    
  }
}
//
void timtu(BTA *root){
  char tucantim[20] = "", nghia[MAX] = "";
  int i, j;
  printf("Nhap tu can tim: ");
  scanf("%[^\n]", tucantim);
  
  gets(dem);
  j = btsel(root, tucantim, nghia, sizeof(nghia), &i);
  if(j == 0) printf("%s\n%s\n", tucantim, nghia);
  else printf("*Error* tu nay khong co trong tu dien!\n");
}
void themtu(BTA *root){
  char tucanthem[20] = "", nghia[MAX] = "";
  int i, j;
  printf("Nhap tu can them vao tu dien: ");
  scanf("%[^\n]", tucanthem);
  
  gets(dem);
  j = btsel(root, tucanthem, nghia, sizeof(nghia), &i);
  if(j == 0) {
    printf("*Error* tu nay da co trong tu dien!\n");
    printf("%s\n%s\n", tucanthem, nghia);
  }
  else{
    printf("Nghia cua tu: ");
    scanf("%[^\n]", nghia);
    gets(dem);
    btins(root, tucanthem, nghia, (strlen(nghia) + 1)*sizeof(char));
    printf("Them tu thanh cong.\n");
  }
}

void xoatu(BTA *root){
  char tucanxoa[20] = "", nghia[MAX] = "";
  int i, j;
  printf("Nhap tu can xoa khoi tu dien: ");
  scanf("%[^\n]", tucanxoa);
  
  gets(dem);
  j = btsel(root, tucanxoa, nghia, sizeof(nghia), &i);
  if(j != 0) {
    printf("*Error* tu nay khong co trong tu dien!\n");
  }
  else{
    printf("%s\n%s\n", tucanxoa, nghia);
    printf("Ban co chac muon xoa tu nay ? 1: yes / 0: no ");
    scanf("%d", &i);
    gets(dem);
    if(i == 1){
      btdel(root, tucanxoa);
      printf("Xoa tu thanh cong.\n");
    }
  }
}
int main(){
  int luachon;
  btinit();
  BTA *root;
  btree(&root);
  scanf("%d", &luachon);
  gets(dem);
  switch(luachon){
  case 1: timtu(root); break;
  case 2: themtu(root); break;
  case 3: xoatu(root); break;
  default: printf("*Error* Lua chon khong hop le!\n"); break;
  }
  btcls(root);
  return 0;
}
