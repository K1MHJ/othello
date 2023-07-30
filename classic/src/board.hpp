#pragma once
#include "coin.hpp"
#include <vector>
using namespace std;

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
    coin_map[y * size_w + x] = &coin;
    coin_exist[y * size_w + x] = true;
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
    contents[y * board_length + x] = coin;
  }
  int get(int y, int x){
    return contents[y * board_length + x];
  }
  int contents[100];
  int size;
  const int board_length = 8;
private:
};
