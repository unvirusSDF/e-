#include "../../include/imports.hpp"

#include <ctime>

namespace epp {
  
  void init_nc(){// initialize ncurses
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

    init_color(COLOR_BLUE,600,200,400);
    init_color(COLOR_YELLOW, 200, 600, 400);

    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);




    cbreak();
    refresh();

  }

  void end(void (*lambda)(void)){//end the process and exit the programm the lambda is used if you want to do something special before exiting, like wait until a key is pressed
    lambda();
    endwin();
    exit(EXIT_SUCCESS);
  }

  int rand(int min, int maj){//generate random numbers
    int res=((( (long int) &maj)*CLOCKS_PER_SEC));
    res%= std::clock();
    return (int) (res%(maj-min))+min;
  }

  void _sleep(unsigned long long time){
    size_t start = std::clock(); //take the begin time
    while (1000*(std::clock()-start)<time*CLOCKS_PER_SEC) {} //wait;
  }


  uint8_t quit_count=0;

  void quit(uint8_t quit_c){ //used to exit menus, this is use to set a number that represent how many things you'll have to exit
    quit_count=quit_c;
  }

  uint8_t quited(){ // used for the conditional to exit the menu, works with quit(), if it return non-zero this means that you'll have to exit
    return ((quit_count)? quit_count-- : 0);
  }

}
