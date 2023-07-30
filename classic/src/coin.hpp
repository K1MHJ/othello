#pragma once

#define WHITE 0
#define BLACK 1
#define HINT  2

class Coin{
public:
  typedef enum{
    CWHITE,
    CBLACK,
    CHINT
  }COLOR;
  Coin(){
    upper_color = CWHITE;
  }
  Coin& operator = (const Coin& rhs){
    if (this != &rhs)
    { 
      this->upper_color = rhs.upper_color;
    }
    return *this;
  }
  void PutOn(COLOR _color){
    upper_color = _color;
  }
  COLOR UpColor(){
    return upper_color;
  }
  void Flip(){
    if(upper_color == CBLACK){
      upper_color = CWHITE;
    }else{
      upper_color = CBLACK;
    }
  }
private:
  COLOR upper_color;
};
