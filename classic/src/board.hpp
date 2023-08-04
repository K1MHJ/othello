#pragma once
#include "coin.hpp"
#include <vector>
using namespace std;

void dprint(const char* format, ...);

class GameBoard{
private:
  int size_w, size_h;
  Coin* coin_map[100];
  bool coin_exist[100];
public:
  GameBoard(int w, int h){
    this->size_w = w;
    this->size_h = h;
    for(int i = 0;i<size_w*size_h;i++){
      coin_map[i] = nullptr;
      coin_exist[i] = false;
    }
  }
  ~GameBoard(){}
  int getW() const{
    return size_w;
  }
  int getH() const{
    return size_h;
  }
  Coin* getCoin(int y, int x){
    if(coin_exist[y * size_w + x]){
      return coin_map[y * size_w + x];
    }
    return nullptr;
  }
  void clear(){
    for(int i = 0;i<size_w*size_h;i++){
      coin_exist[i] = false;
      coin_map[i] = nullptr;
    }
  }
  void PutCoinOnBoard(int y, int x, Coin& coin){
    int i = y * size_w + x;
    coin_map[i] = &coin;
    coin_exist[i] = true;
    Coin::COLOR ally = coin.UpColor();
    Coin::COLOR enemy = (ally == Coin::CBLACK)? Coin::CWHITE: Coin::CBLACK;
	  int r;
	  static int dxy[8] = { -8, -7, 1, 9, 8, 7, -1, -9 };
    for(int ui = 0 ; ui < 8 ; ui++){
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
        if(!coin_exist[r]){
          k = 0;
          break;
        }
        if(coin_map[r]->UpColor() == enemy){
          r += dxy[ui];
        }
        else if(coin_map[r]->UpColor() == ally){
          break;
        }else{
          k = 0;
          break;
        }
      }
      if(k > 0)
      {
        while( k-- > 0 ){
          r -= dxy[ui];
          if(r < 0 || 64 <= r){
            break;
          }
          coin_map[r]->Flip();
        }
      }
    }
  }
private:
  bool check(int y, int x){
    if(x < 0 || x >= size_w
    || y < 0 || y >= size_h){
      return false;
    }
    return true;
  }
};
class virtualBoard{
public:
  virtualBoard(){}
  virtualBoard(const virtualBoard &t) {
    this->size = t.size;
    memcpy(this->contents, t.contents, sizeof(int) * 100);
  }
  virtualBoard& operator=(const virtualBoard &t) {
    this->size = t.size;
    memcpy(this->contents, t.contents, sizeof(int) * 100);
    return *this;
  }
  ~virtualBoard(){}
  void PutOn(int y, int x, int coin){
    int i = y * board_length + x;
    contents[i] = coin;
    int enemy_coin = coin * -1;
	  int r;
    int k;
	  static int dxy[8] = { -8, -7, 1, 9, 8, 7, -1, -9 };
    for(int ui = 0 ; ui < 8 ; ui++){
      r = i + dxy[ui];
      for(k = 0 ; k < 10; k++)
      {
        if(r < 0 || 64 <= r){
          k = 0;
          break;
        }
        if(contents[r] == enemy_coin){
          r += dxy[ui];
        }
        else if(contents[r] == coin){
          break;
        }else{
          k = 0;
          break;
        }
      }
      if(k > 0)
      {
        while( --k >= 0 ){
          r -= dxy[ui];
          if(r < 0 || 64 <= r){
            break;
          }
          contents[r] = coin;
        }
      }
    }
  }
  int get(int y, int x){
    return contents[y * board_length + x];
  }
  int contents[100];
  int size;
  const int board_length = 8;
private:
};
