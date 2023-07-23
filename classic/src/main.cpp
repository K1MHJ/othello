#include <curses.h>
#include <locale.h>
#include "game.hpp"

int main(int argc, char ** argv)
{
  initscr(); //start ncurses window
  setlocale(LC_ALL, "");
  refresh();
  noecho(); //キーが入力されても表示しない
  curs_set(0);//カーソルを非表示

  Game game;
  
  game.start();
  while(!game.isOver())
  {
    game.processInput();
    game.updateState();
    game.redraw();
  }
  getch();
  endwin();

  return 0;
}
