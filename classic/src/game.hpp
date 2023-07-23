#pragma once
#include <ncurses.h>
#include <string>
#include "gui.hpp"
#include "player.hpp"
#include "coin.hpp"
#include "board.hpp"
#include "engine.hpp"

using namespace std;

class Game{
  Gui gui;
  bool game_over;
  GameEngine engine; 

public:
  Game(){
    gui.initialize();
    game_over = false;
  };
  ~Game(){
  };
  void start(){
    engine.reset();
    gui.setEngine(engine);
  }
  void processInput(){
    chtype input = gui.getInput();
  }
  void updateState(){
    engine.update();
  }
  void redraw(){
    gui.redraw();
  }
  bool isOver(){
    return game_over;
  }
};
