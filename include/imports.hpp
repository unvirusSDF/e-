#pragma once

#include <ncurses.h>
#include <iostream>

#include "./dlc.hxx"
#include "./tui/tui.hpp"

namespace epp {

  void init_nc(void);
  void end(void (*)(void));
  int rand(int, int);

  inline void rst_scr(short int y=0, short int x=0, short int h=0, short int w=0);


}
