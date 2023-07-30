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
    getCandidate(candidates, top_board);
    for(auto it = candidates.begin();it!=candidates.end();it++){
      h->push_back(pair<int,int>(it->y,it->x));
    }
    return;
  } 
  void DoPlay(){
    virtualBoard top_board;
    dprint("Player(%s) has %d Coins.", (myColor == Coin::CWHITE)? "White":"Black", coinbag.size());
    top_board.size = board->getH() * board->getW();
    for(int y = 0; y < board->getH();y++){
      for(int x = 0;x < board->getW();x++){
        top_board.contents[y * board->getW() + x] = GetCoin(y,x);
      }
    }
    stPos best_action;
    if(INT_MIN < minimax(&best_action, top_board, 3, true)){
      Coin* coin = coinbag.top();
      coinbag.pop();
      board->PutCoinOnBoard(best_action.y, best_action.x, *coin);
    }
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
  int minimax(stPos* next_action, virtualBoard& board, int depth, bool maxplayer) {
    int value = 0;
    stPos best_action;
    vector<stPos> candidates;
    virtualBoard next_board;
    if(depth == 0){
      return heuristicsValue(board);
    }
    value = maxplayer ? INT_MIN:INT_MAX;
    getCandidate(candidates, board);
    
    for(auto it = candidates.begin();it != candidates.end();it++){
      next_board = board;
      next_board.PutOn(it->y, it->x, ALLY);
      int each_value = minimax(&best_action,next_board, depth - 1, !maxplayer);
      if((maxplayer && value < each_value) || (!maxplayer && value > each_value)){
        value = each_value;
        *next_action = *it;
      }
    }
    return value;
  }
  void getCandidate(vector<stPos> &candidates, virtualBoard &board){
	  int r;
	  static int dxy[8] = { -8, -7, 1, 9, 8, 7, -1, -9 };
    for(int i = 0;i<board.board_length * board.board_length;i++){
      if(board.contents[i] != ALLY){
        continue;
      }
      for(int ui = 0;ui < 8;ui++){
        r = i + dxy[ui];
        int k;
        for(k = 0 ; k < 10; k++)
        {
          if(r < 0 || 64 <= r){
            k = 0;
            break;
          }
          if(board.contents[r] == ENEMY){
            r += dxy[ui];
          }
          else if(board.contents[r] == ALLY){
            k = 0;
            break;
          }else{
            break;
          }
        }
        if(k > 0 && board.contents[r] == EMPTY)
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
