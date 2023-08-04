#pragma once
#include "board.hpp"
#include "coin.hpp"
#include "gui.hpp"
#include <cctype>
#include <stack>
#include <array>
#include <vector>
using namespace std;

extern Gui * gui;
void dprint(const char* format, ...);

class GamePlayer{
  typedef struct{
    int y;
    int x;
  }stPos;
  typedef struct {
    int kinds;
    int y;
    int x;
  }CINFO;
  enum{
    ENEMY = -1,
    EMPTY = 0,
    ALLY  = 1,
  }KINDS;
public:
  GamePlayer(){};
  ~GamePlayer(){};
  void ShowHint(vector<pair<int,int>> *h){
    virtualBoard top_board;
    top_board.size = board->getH() * board->getW();
    for(int y = 0; y < board->getH();y++){
      for(int x = 0;x < board->getW();x++){
        top_board.contents[y * board->getW() + x] = GetCoin(y,x);
      }
    }
    vector<stPos> candidates;
    getCandidate(candidates, top_board, true);
    for(auto it = candidates.begin();it!=candidates.end();it++){
      h->push_back(pair<int,int>(it->y,it->x));
    }
    return;
  } 
  bool DoPlay(){
    virtualBoard top_board;
    top_board.size = board->getH() * board->getW();
    for(int y = 0; y < board->getH();y++){
      for(int x = 0;x < board->getW();x++){
        top_board.contents[y * board->getW() + x] = GetCoin(y,x);
      }
    }
    stPos best_action;
    int depth = 0;
    if(myColor == Coin::CBLACK){
      depth = 1;
    }else if(myColor == Coin::CWHITE){
      depth = 2;
    }
    int val = minimax(&best_action, top_board, depth, true);
    if(INT_MIN == val){
      return false;
    }else{
      Coin* coin = coinbag.top();
      coinbag.pop();
      dprint("Action : %d, %c", best_action.x + 1, 'a'+best_action.y);
      board->PutCoinOnBoard(best_action.y, best_action.x, *coin);
      return true;
    }
    return false;
  }
  int heuristicsValue(virtualBoard& board){
    int score_ally = 0;
    int score_enemy = 0;
    for(int i = 0;i<board.size;i++){
      if(board.contents[i] == ALLY){
        score_ally++;
      }else if(board.contents[i] == ENEMY){
        score_enemy++;
      }
    }
    return score_ally - score_enemy;
  }
  int minimax(stPos* next_action, virtualBoard& board, int depth, bool ally) {
    int value = 0;
    stPos best_action;
    vector<stPos> candidates;
    virtualBoard next_board;
    if(depth == 0){
      return heuristicsValue(board);
    }
    value = ally ? INT_MIN:INT_MAX;
    getCandidate(candidates, board, ally);
    if(candidates.size() == 0){
      return value;
    }
    for(auto it = candidates.begin();it != candidates.end();it++){
      next_board = board;
      next_board.PutOn(it->y, it->x, ALLY);
      int each_value = minimax(&best_action,next_board, depth - 1, !ally);
      if((ally && value < each_value) || (!ally && value > each_value)){
        value = each_value;
        *next_action = *it;
      }
    }
    return value;
  }
  void getCandidate(vector<stPos> &candidates, virtualBoard &board, bool ally){
	  int r;
	  static int dxy[8] = { -8, -7, 1, 9, 8, 7, -1, -9 };
    int my = ally? ALLY:ENEMY;
    int anti = !ally? ALLY:ENEMY;
    for(int i = 0;i<board.board_length * board.board_length;i++){
      if(board.contents[i] != my){
        continue;
      }
      for(int ui = 0;ui < 8;ui++){
        r = i + dxy[ui];
        int k;
        for(k = 0 ; k < 10; k++)
        {
          if(dxy[ui] == 1 || dxy[ui] == -7 || dxy[ui] == 9){
            if(r % 8 <= i % 8){
              k = 0;
              break;
            }
          }
          if(dxy[ui] == -1 || dxy[ui] == -9 || dxy[ui] == 7){
            if(r % 8 >= i % 8){
              k = 0;
              break;
            }
          }
          if(r < 0 || 64 <= r){
            k = 0;
            break;
          }
          if(board.contents[r] == anti){
            r += dxy[ui];
          }
          else if(board.contents[r] == my){
            k = 0;
            break;
          }else{
            break;
          }
        }
        if(k > 0)
        {
          stPos p;
          p.x = r % board.board_length;
          p.y = r / board.board_length;
          candidates.push_back(p);
        }
      }
    }
  }
  void TakeCoin(Coin &coin){
    coinbag.push(&coin);
  }
  void RemoveCoins(){
    stack<Coin*>().swap(coinbag);
  }
  void setBoard(GameBoard *board){
    this->board = board;
  }
  void selectColor(char color){
    color = tolower(color); 
    if(color == 'w'){
      myColor = Coin::CWHITE;
    }else if(color == 'b'){
      myColor = Coin::CBLACK;
    }
  }
private:
  int GetCoin(int y, int x){
    Coin* c = board->getCoin(y, x);
    if(c == nullptr){
      return EMPTY;
    }
    if(myColor == c->UpColor()){
      return ALLY; //meaning my coin
    }else{
      return ENEMY; //enemy coin
    }
  }

private:
  GameBoard* board;
  Coin::COLOR myColor;
  stack<Coin*> coinbag;
};
