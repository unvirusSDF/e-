#pragma once

#include <ncurses.h>
#include <iostream>

#include <cmath>

#include "./tui/tui.hpp"
#include "./game/game.hpp"

namespace epp {

  void init_nc(void);
  void end(void (*)(void));
  int rand(int, int);
  void _sleep(unsigned long long);

  inline void rst_scr(short int y=0, short int x=0, short int h=0, short int w=0);

  void quit(uint8_t q=1);

  uint8_t quited();

}
