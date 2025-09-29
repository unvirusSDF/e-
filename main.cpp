#include <iostream>

#include "./include/imports.hpp"



int main (int argc, char *argv[]) {
  
  using namespace epp;

  int HEIGHT, WIDTH;
  getmaxyx(stdscr,HEIGHT,WIDTH);

  
  init_nc();

  settings s{0,20,20,0,0,2,5}; //generate a settings pack for a basic menu

  menu home(std::vector<menu_opts>{
      menu_opts( (char*) "exit",[](void){
            endwin();
            exit(EXIT_SUCCESS);
          }),
      menu_opts( (char*) "gamble",[](void){
            text_box u(20,30,rand(0,41-20),rand(0,191-30));
            u.line(0,"main");
            u.line(2,"i think that you won");
            u();

          })
      }, s,true);

  home();

  

  //l_menu();

  end([](void){
      noecho();
      do{}while (getch()!='q');//wait 'til it ends
    });

  return 0;
}
