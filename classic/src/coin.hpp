#pragma once

class Coin{
public:
  Coin(){
    y=x=0;
    icon=' ';
  }
  Coin(int y, int x, char ch){
    this->x = x;
    this->y = y;
    this->icon = ch;
  }
  int getX(){return x;}
  int getY(){return y;}
  char getIcon(){return icon;}
private:
  int x;
  int y;
  char icon;
};
