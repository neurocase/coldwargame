#include <stdio.h>
#include "mymap.xpm"

/*

int main(int argv, char* argc[]){
  int i = 0;
 for(i = 0; i < 20; i++){
   char mymapchar = *map_xpm[i];
  printf("%s ; %c ;",map_xpm[i], getMapChar(i,1));
  printf("sizeof %d \n",map_xpm[i]);
 }
} */

int getMapChar(int x, int y){
  y = y+5;
  if (map_xpm[y][x]){
    return map_xpm[y][x];
  }else{
    return "N";
  }
}
