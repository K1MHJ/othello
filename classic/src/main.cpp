#include <curses.h>
#include <locale.h>
#include <thread>
#include "game.hpp"
#include "gui.hpp"

Gui * gui;

void dprint(const char* format, ...){
  char buffer[256];
  va_list ap;
  va_start(ap, format);
  vsnprintf(buffer, 256, format, ap);
  va_end(ap);
  gui->printf("%s", buffer);
};

int main(int argc, char ** argv)
{
  initscr(); //start ncurses window
  setlocale(LC_ALL, "");
  refresh();
  noecho(); //キーが入力されても表示しない
  curs_set(0);//カーソルを非表示
  gui = new Gui; 
  Game game;
  game.start();
  game.redraw();

  while(game.processInput())
  {
    game.redraw();
  }
  endwin();
  delete gui;

  return 0;
}
