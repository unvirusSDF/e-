#pragma once

#include <ncurses.h>

namespace epp {

  struct color {
    uint8_t R,G,B;
  };

  uint8_t use(WINDOW*, color);
  void stop_color(WINDOW*);

}
