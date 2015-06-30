#include <ncurses.h>
#include "mymap.xpm"




char myMap[20 * 110];

void drawHUD(){
  int i = 0;
  int j = 0;
  int c = 0;
  short pb = 0;
  const char* cb[4] = {&myMap[0],"b", "c", "d"};
  init_pair(2,COLOR_YELLOW,COLOR_RED);
  while(i <= 26){
    while(j <= 111){
      if (i == 0 || i == 26 || j == 0 || j == 111){
          attron(COLOR_PAIR(2));
          char c = 'a';
          if (i == 0 || i ==26){
            c = 'i';
          }else if (j == 0 || j == 111){
            c = 'h';
          }
          mvprintw(i,j,"%c",c);
          attroff(COLOR_PAIR(2));
      }else{
          mvprintw(i,j,"%c",getMapChar(j-1,i-1));
      }
      j++;
    } 
    i++;
    j = 0;
  }
        char *mapChar = myMap[0];
        mvprintw(1,1,"%c", myMap[2]);    
}

int main(int argv, char * argc[])
{
  int ch, row, col;
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();
  getmaxyx(stdscr,row,col);

  while((ch=getch())!=27){
    start_color();
    drawHUD();

    init_pair(1,COLOR_BLACK, COLOR_RED);
    attron(COLOR_PAIR(1));
    mvprintw(row/4,col/4, "Cold War");
    attroff(COLOR_PAIR(1));
    mvprintw(row/4+1,col/4," Screen Size is: %d x %d", row, col);
    move(21,1); 
    printw(" The Key pressed is: ");
    attron(A_BOLD);
    printw("%c : Keycode : %d", ch, ch);
    attroff(A_BOLD);
    
    refresh();
  }
  
  endwin();

  return 0;
}
