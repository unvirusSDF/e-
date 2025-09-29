#include "../../include/imports.hpp"

namespace epp {

  bool existing_pair[16];

  uint8_t use(WINDOW* win, color c){
    wattroff(win, 0);
    short int r=4*c.R;
    short int g=4*c.G;
    short int b=4*c.B;

    int i=0;
    for (; i < 16; i++) {
      if(existing_pair[i]) break;
    }

    init_color(COLOR_WHITE,(r<1000)? r : 999, (g<1000)? g : 999 , (b<1000)? b : 999);
    init_pair(i, COLOR_WHITE, COLOR_BLACK);
    wattron(win, COLOR_PAIR(0));
    return i;
  }

  void stop_color(WINDOW* win, uint8_t id){
    existing_pair[id]=0;
    wattroff(win,COLOR_PAIR(id));
  }
}


