#include "../../include/imports.hpp"



namespace epp {

  struct string{
    int len;
    char* str;
  };

  string* logs = nullptr;
  short int current_line=0;
  WINDOW* log;

  short int H,W;
  
  void startlog(){

    getmaxyx(stdscr,H,W);
    mvprintw(1,1,"H,W = %i,%i",H,W);
    { // create the box
      WINDOW* log_box = newwin(H,50,0,W-50);  
      box(log_box,0,0);
      wattron(log_box, COLOR_PAIR(2));
      mvwprintw(log_box, 0,1,"logs");
      wattroff(log_box, COLOR_PAIR(2));
      wrefresh(log_box);
    }

    log = newwin(H-2,48,1,W-49);

    logs = new string[H-2];
    for(int i=0; i<H-2;i++){
      logs[i]=string{1,new char[1]};
    }
    current_line=0;

  }

  void printlog(char* str){
    int len;
    for (int i = 0; str[i]!='\0' ; i++, len++) {}
    string line;
    line.str = new char[len+3];
    sprintf(line.str, "%c%c%s",'>',' ', str);
    line.len=len;
    
    delete logs[current_line].str;
    logs[current_line]=line;

    current_line+=line.len/48 +1;
    current_line%=H-2;

    for(short int i = 0; i<H-2;) {
      mvwprintw(log,H-3-i,0,"%s",logs[(i+current_line)%(H-2)].str);
      i+= logs[(i+current_line)%(H-2)].len/48 +1;
    }
    wrefresh(log);
  }

  void endlog(){
    for (int i = 0; i<H-2 ; i++) {
      delete logs[i].str;
    }
    delete logs;
    logs=nullptr;
  }

}


