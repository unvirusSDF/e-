#include <iostream>

#include "./include/imports.hpp"

#include <string>


int main (int argc, char *argv[]) {
  
  using namespace epp;


  init_nc();

  short int HEIGHT, WIDTH;
  getmaxyx(stdscr,HEIGHT,WIDTH);

  settings s{0,HEIGHT,WIDTH,0,0,2,5,1,2}; //generate a settings pack for a basic menu

  menu(std::vector<menu_opts>{
      menu_opts( (char*) "exit",[](void){
          endwin();
          quit();
        }),
      menu_opts( (char*) "gamble",[](void){
          int W,H;
          getmaxyx(stdscr,H,W);
          text_box u(20,30,rand(0,H-20),rand(0,W-30),1,3,4);
          u.line(0,"main");
          u.line(2,"i think that you won");
          u();
        }),
      menu_opts( (char*) "play",main_bis)}, s);

    endwin();


  std::cout << "until there it works" << std::endl;
 

  return 0;
}
