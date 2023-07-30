#pragma once
#include <ncurses.h>
#include <string>
#include <string.h>
#include "gui.hpp"
#include "player.hpp"
#include "coin.hpp"
#include "board.hpp"

using namespace std;
extern Gui* gui;

void dprint(const char* format, ...);

class Game{
  bool game_over;
  Coin coins[100];
  GameBoard board = GameBoard(8,8);
  GamePlayer player[2];
  char menu_selected[256];
  chtype key_input;
  int playturn;
  Coin *bag[2];
public:
  Game(){
    playturn = 0;
    game_over = false;
    player[WHITE].setBoard(&board);
    player[WHITE].selectColor('W');
    player[BLACK].setBoard(&board);
    player[BLACK].selectColor('B');
  };
  ~Game(){
  };
  void start(){
    gui->initialize();
    Reset();
    ShowNextTurn();
  }
  bool processInput(){
    if(gui->getInput(menu_selected, &key_input)){
      dprint("Pressed %s", menu_selected);
      if(0 == strcmp(menu_selected, "Quit")){
        return false;
      }else if(0 == strcmp(menu_selected, "Next")){
        Next();
        ShowNextTurn();
      }else if(0 == strcmp(menu_selected, "Reset")){
        Reset();
      }
    }
    return true;
  }
  void ShowNextTurn(){
    ShowHint();
  }
  void ShowHint(){
    vector<pair<int,int>> h;
    player[playturn].ShowHint(&h); 
    dprint("Hint:%s %d",(playturn == WHITE)?"White":"Black", h.size());
    gui->clearNotCoin();
    for(auto it = h.begin();it!=h.end();it++){
      gui->addAt(it->first, it->second, 'O');
    }
  }
  void Reset(){
    int coin_no = 63;
    board.clear();
    board.PutCoinOnBoard(2,2,coins[coin_no]);coins[coin_no--].PutOn(Coin::CWHITE);
    board.PutCoinOnBoard(3,3,coins[coin_no]);coins[coin_no--].PutOn(Coin::CWHITE);
    board.PutCoinOnBoard(3,2,coins[coin_no]);coins[coin_no--].PutOn(Coin::CBLACK);
    board.PutCoinOnBoard(2,3,coins[coin_no]);coins[coin_no--].PutOn(Coin::CBLACK);

    player[0].RemoveCoins();
    player[1].RemoveCoins();
    for(;coin_no >= 0;coin_no--){
      player[coin_no % 2].TakeCoin(coins[coin_no]);
    }
    playturn = WHITE;
  }
  void Next(){
    if(playturn == WHITE){
      playturn = BLACK;
    }else{
      playturn = WHITE;
    }
    player[playturn].DoPlay(); 
  }
  void redraw(){
    gui->drawBoardContents(board);
  }
  bool isOver(){
    return game_over;
  }
  GameBoard* GetBoard(){
    return &board;
  }
};

