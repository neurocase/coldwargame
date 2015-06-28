#include <ncurses.h>





void drawHUD(){

  int i = 0;
  int j = 0;
  int c = 0;
  short pb = 0;
  const char cb[4] = {'a','b', 'c', 'd'};
  init_pair(2,COLOR_YELLOW,COLOR_RED);
  attron(COLOR_PAIR(2));
  while(i < 21){
    while(j < 100){
      pb = 0;
      if (i == 0 || i == 20){
        pb = 1;
      }else if(j == 1){
        j = 99;
      }
      if (j == 0 || 100){
         pb = 1;
      }
      if (pb == 1){
        mvprintw(i,j,"x");    
      }
      j++;
    }
    
    i++;
    j = 0;
  }
  attroff(COLOR_PAIR(2));
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
    move(1,1); 
    printw(" The Key pressed is: ");
    attron(A_BOLD);
    printw("%c : Keycode : %d", ch, ch);
    attroff(A_BOLD);
    
    refresh();
  }
  
  endwin();


  return 0;



}
