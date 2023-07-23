#pragma once
#include <string>
#include <curses.h>
#include <locale.h>
#include <cstdio>
#include <stdio.h>
#include "coin.hpp"
#include "engine.hpp"
using namespace std;
class Gui
{
  int box_w, box_h;
  const string cb[3] 
    = {
      "+---+",
      "|   |",
      "+---+"
    };
public:
  Gui(){
    int xMax, yMax;
    box_w = 1 + dimension * (3 + 1) + 3;
    box_h = dimension * 2 + 1 + 1;
    getmaxyx(stdscr, yMax, xMax);
    board_win = newwin(box_h,box_w, 0,0);
  }
  ~Gui(){}
  void initialize(){
    clear();
    refresh();
  }
  void setEngine(GameEngine& engine){
    this->engine = &engine;
  }
  void addBorder(){
    char buf[12];
    mvwaddstr(board_win,0,0,"   ");
    for(int y=0;y<dimension;y++){
      char alp = 'a'+y;
      sprintf(buf, " %c ", alp);
      mvwaddstr(board_win,y*2+1,0,"---");
      mvwaddstr(board_win,y*2+2,0,buf);
      mvwaddstr(board_win,y*2+3,0,"---");
    }
    for(int x=0;x<dimension;x++){
      sprintf(buf, "|%03d|", x+1);
      mvwaddstr(board_win,0,x*4+3,buf);
    }
    for(int y=0;y<dimension;y++){
      for(int x=0;x<dimension;x++){
        mvwaddstr(board_win, y * 2+1, x * 4+3, cb[0].c_str());
        mvwaddstr(board_win, y * 2+2, x * 4+3, cb[1].c_str());
        mvwaddstr(board_win, y * 2+3, x * 4+3, cb[2].c_str());
      }
    }
  }
  void addAt(int y, int x, char ch){
    mvwaddch(board_win, y*2+1+1, x*4+2+3, ch);
  }
  chtype getInput(){
    return wgetch(board_win);
  }
  void clear(){
    wclear(board_win);
    addBorder();
  }
  void refresh(){
    wrefresh(board_win);
  }
  void redraw(){
    for(int y = 0;y<engine->GetBoard()->getH() ;y++){
      for(int x = 0;x<engine->GetBoard()->getW();x++){
        char c = engine->GetBoard()->getCell(y, x);
        addAt(y, x, c); 
      }
    }
  }
private:
  WINDOW * board_win;
  const int dimension = 8;
  GameEngine* engine;
};
