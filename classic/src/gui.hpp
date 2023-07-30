#pragma once
#include <string>
#include <curses.h>
#include <locale.h>
#include <cstdio>
#include <stdio.h>
#include "board.hpp"
#include <queue>
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
    menu_win  = newwin(menu_h,xMax, yMax - menu_h,0);
    debug_win = newwin(yMax-menu_h,debug_w,0,xMax-debug_w);
    report_win= newwin(yMax-menu_h,report_w,0,xMax-(report_w+debug_w));
  }
  ~Gui(){}
  void initialize(){
    wtimeout(menu_win, -1);
    wtimeout(board_win, -1);
    wtimeout(debug_win, -1);
    wtimeout(report_win, -1);
    box(menu_win, 0,0);
    box(debug_win,0,0);
    box(report_win,0,0);
    mvwaddstr(menu_win,0,2,"<MENU>");
    mvwaddstr(debug_win,0,2,"<DEBUG LOG>");
    mvwaddstr(report_win,0,2,"<REPORT>");
    drawBoard();
    keypad(menu_win, true);
    menu_select = 0;
    selectMenu();
    refresh();
    mvwprintw(debug_win,1,1,"");
  }
  void printf(const char* format, ...){
    char buffer[256];
    int width = getmaxx(debug_win);
    int height = getmaxy(debug_win);
    for(int i = height-3;i>=1;i--){
      mvwinnstr(debug_win,i,1,buffer,width-2); 
      mvwaddstr(debug_win,i+1,1,buffer);
    }
    va_list ap;
    va_start(ap, format);
    vsnprintf(buffer, 256, format, ap);
    va_end(ap);
    for(int i = strlen(buffer);i<width-2;i++){
      strcat(buffer, " ");
    }
    mvwprintw(debug_win,1,1,buffer);
    wrefresh(debug_win);
  }
  void selectMenu(){
    if(menu_select < 0){
      menu_select = 0;
    }
    if(menu_select >= 3){
      menu_select = 2;
    }
    for(int i = 0;i<3;i++){
      if(i == menu_select)
        wattron(menu_win, A_REVERSE);
      mvwprintw(menu_win, i+1,1,menu[i].c_str());
      wattroff(menu_win, A_REVERSE);
    }
  }
  void drawBoard(){
    char buf[12];
    mvwaddstr(board_win,0,0,"   ");
    for(int y=0;y<dimension;y++){
      char alp = 'a'+y;
      snprintf(buf,12, " %c ", alp);
      mvwaddstr(board_win,y*2+1,0,"---");
      mvwaddstr(board_win,y*2+2,0,buf);
      mvwaddstr(board_win,y*2+3,0,"---");
    }
    for(int x=0;x<dimension;x++){
      snprintf(buf,12, "|%03d|", x+1);
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
  void clearNotCoin(){
    for(int y = 0;y<8 ;y++){
      for(int x = 0;x<8;x++){
        char c = readAt(y,x);
        if(c != 'W' && c != 'B'){
          addAt(y, x, ' ');
        }
      }
    }
  }
  char readAt(int y, int x){
    return mvwinch(board_win, y*2+1+1, x*4+2+3);
  }
  void addAt(int y, int x, char ch){
    mvwaddch(board_win, y*2+1+1, x*4+2+3, ch);
  }
  void refresh_board(){
    wrefresh(board_win);
  }
  bool getInput(char* menu_text, chtype *key_in){
    chtype choice;
    choice = wgetch(menu_win);
    switch(choice){
      case KEY_UP:
        menu_select--;
        selectMenu();
        break;
      case KEY_DOWN:
        menu_select++;
        selectMenu();
        break;
      case '\n':
        strcpy(menu_text, menu[menu_select].c_str());
        return true;
      default:
        return false;
    }
    return false;
  }
  void refresh(){
    wrefresh(board_win);
    wrefresh(menu_win);
    wrefresh(debug_win);
    wrefresh(report_win);
  }
  void drawBoardContents(GameBoard& board){
    Coin* c = nullptr;
    for(int y = 0;y<board.getH() ;y++){
      for(int x = 0;x<board.getW();x++){
        c = board.getCoin(y, x);
        if(c != nullptr){
          if(WHITE == c->UpColor()){
            addAt(y, x, 'W'); 
          }else if(BLACK == c->UpColor()){
            addAt(y, x, 'B'); 
          }
        }
      }
    }
    wrefresh(board_win);
  }
private:
  const int menu_h = 10;
  const int report_w = 40;
  const int debug_w = 40;
  string menu[3] = {"Next", "Reset", "Quit"};
  int menu_select = 0;
  WINDOW * board_win;
  WINDOW * menu_win;
  WINDOW * debug_win;
  WINDOW * report_win;
  const int dimension = 8;
};

