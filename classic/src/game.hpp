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
  int score_white;
  int score_black;
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
      if(0 == strcmp(menu_selected, "Quit")){
        return false;
      }else if(0 == strcmp(menu_selected, "Next")){
        if(!game_over){
          Next();
        }else{
          dprint("Game Over");
          dprint("Press Reset to continue.");
        }
      }else if(0 == strcmp(menu_selected, "Reset")){
        dprint("Pressed Reset");
        gui->initialize();
        Reset();
        ShowNextTurn();
        game_over = false;
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
    gui->clearNotCoin();
    for(auto it = h.begin();it!=h.end();it++){
      gui->addAt(it->first, it->second, '*');
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
      switch(coin_no % 2){
        case WHITE:
          coins[coin_no].PutOn(Coin::CWHITE);
          player[WHITE].TakeCoin(coins[coin_no]);
        break;
        case BLACK:
          coins[coin_no].PutOn(Coin::CBLACK);
          player[BLACK].TakeCoin(coins[coin_no]);
        break;
      }
    }
    playturn = WHITE;
  }
  void JudgeWinLose(){
    for(int y=0;y<8;y++){
      for(int x=0;x<8;x++){
        Coin* c = board.getCoin(y, x);
        if(c != nullptr){
          if(Coin::CWHITE == c->UpColor()){
            score_white++;
          }else{
            score_black++;
          }
        }
      }
    }
    if(score_white > score_black){
      dprint("Winner is White!");
    }else if(score_white < score_black){
      dprint("Winner is Black!");
    }else{
      dprint("No One win!!");
    }
    game_over = true;
  }
  void ShowScoreBoard(){
    score_black = score_white = 0;
    for(int y=0;y<8;y++){
      for(int x=0;x<8;x++){
        Coin* c = board.getCoin(y, x);
        if(c != nullptr){
          if(Coin::CWHITE == c->UpColor()){
            score_white++;
          }else{
            score_black++;
          }
        }
      }
    }
    gui->printr("SCORE White:Black = %d : %d", score_white, score_black);
  }
  void Next(){
    if(!player[playturn].DoPlay()){
      ShowScoreBoard();
      JudgeWinLose();
      return;
    }
    ShowScoreBoard();
    if(playturn == WHITE){
      playturn = BLACK;
    }else{
      playturn = WHITE;
    }
    dprint("Next Player is %s", (playturn == BLACK)? "Black":"White");
    ShowNextTurn();
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

