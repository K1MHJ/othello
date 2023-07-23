#pragma once
#include <math.h>
#include "board.hpp"
#include "coin.hpp"
using namespace std;

class GameEngine{
  GameBoard board = GameBoard(8,8);
public:
  GameEngine(){
  };
  ~GameEngine(){
  };
  void reset(){
    board.clear();
    board.add(Coin(2,2,'W'));
    board.add(Coin(3,3,'W'));
    board.add(Coin(3,2,'B'));
    board.add(Coin(2,3,'B'));
  } 
  void update(){

  }
  GameBoard* GetBoard(){
    return &board;
  }
};
