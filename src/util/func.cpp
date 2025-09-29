#include "../../include/imports.hpp"

#include <ctime>

namespace epp {
  
  void init_nc(){
    initscr();
    if(!has_colors()){
      endwin();
      std::cerr<<"take  a terminal that can dispaly colors\n\ryou stoopid !\r"<<std::endl;
       exit(-1);
    }
    
    if(!can_change_color()){
      endwin();
      std::cerr<<"you'r less stoopid than I thought,\n\rhowever I want the best colors, so change terminal or kill yourslef\r"<<std::endl;
      exit(-1);
    }

    start_color();

    init_color(COLOR_BLACK,0,0,0);
    init_color(COLOR_MAGENTA, 900,0,900);
    init_color(COLOR_GREEN,100,800,100);
    init_color(COLOR_RED,700,100,100);

    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_WHITE, COLOR_BLACK);


    cbreak();
    refresh();

  }

  void end(void (*lambda)(void)){
    lambda();
    endwin();
  }

  int rand(int min, int maj){
    int res=((long int) &maj)*CLOCKS_PER_SEC;
    res%= std::clock();
    return (res%(maj-min))+min;
  }

}
