#pragma once
#include "coin.hpp"

class GameBoard{
private:
  int size_w, size_h;
  char board[100];

public:
  GameBoard(int w, int h){
    this->size_w = w;
    this->size_h = h;
    clear();
  }
  ~GameBoard(){}
  int getW(){
    return size_w;
  }
  int getH(){
    return size_h;
  }
  char getCell(int y, int x){
    return board[y * size_w + x];
  }
  void clear(){
    for(int i = 0;i<size_w*size_h;i++){
      board[i] = ' ';
    }
  }
  void add(Coin coin){
    if(!check(coin)) return;
    addAt(coin.getY(), coin.getX(), coin.getIcon());
  }
  void addAt(int y, int x, char coin){
    board[y * size_w + x] = coin;
  }
  bool check(Coin coin){
    if(coin.getX() < 0 || coin.getX() >= size_w
    || coin.getY() < 0 || coin.getY() >= size_h){
      return false;
    }
    return true;
  }
};
