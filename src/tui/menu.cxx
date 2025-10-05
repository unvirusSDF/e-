#include "../../include/imports.hpp"

namespace epp {
  
  inline void rst_scr(short int y, short int x, short int h, short int w){//reset the screen
    if((x==0)||(y==0)) getmaxyx(stdscr,h,w); 
    WINDOW* win = newwin(h, w,y,x); //reset the screen
    wrefresh(win);
  }


  void menu(std::vector<menu_opts> opts, settings& s){//render the menu

    WINDOW* _menu = newwin(s.height, s.width, s.pos_y, s.pos_x);

    if(s.boxed) box(_menu,0,0);

    //print the choices
    wattron(_menu, COLOR_PAIR(s.color1));
    for (short int i = 0; i < opts.size(); i++) {
      mvwprintw(_menu, s.height- s.y_space*(i+1),s.x_offset+1, opts.at(i).first);
    }
    wattroff(_menu,COLOR_PAIR(s.color1));
    //initialize the selector
    short int selected=opts.size()-1;
    wattron(_menu, COLOR_PAIR(s.color2));
    mvwprintw(_menu,s.height- s.y_space*(selected+1),s.x_offset, ">");
    wattroff(_menu, COLOR_PAIR(s.color2));
    move(0,0);
    wrefresh(_menu);


    while (1) {// main loop
      //get user input
      noecho();
      const char c = getch();
      if (c=='\n'){ // if enter pressed == "I choose it"
        for (short int i = 0; i < opts.size() ; i++) {
          if (i==selected){
            opts.at(i).second(); //execute the function associated with the coice selected
            break;
          }
        }
        if(quited()) break;
        //run if this is a main menu or if you don't quit it (by using quit())
        //redraw the interface just in case
        if(s.boxed) box(_menu,0,0);

        wattron(_menu, COLOR_PAIR(s.color1));
        for (short int i = 0; i < opts.size(); i++) {
          mvwprintw(_menu, s.height- s.y_space*(i+1), s.x_offset+1, opts.at(i).first);
        }
        wattroff(_menu,COLOR_PAIR(s.color1));
        wattron(_menu, COLOR_PAIR(s.color2));
        mvwprintw(_menu, s.height- s.y_space*(selected+1), s.x_offset, ">");
        wattroff(_menu, COLOR_PAIR(s.color2));
        move(0,0);
        wrefresh(_menu);

      }

      //let's do the frontend and the choice selection
  
      if ((c=='\x1b')&&(getch()=='[')) { //escape sequence + char corresponding to the arrows
        wattron(_menu, COLOR_PAIR(s.color2));
        switch (getch()) {
          case 'B':
            mvwprintw(_menu, s.height-s.y_space*(selected+1), s.x_offset," ");
            (selected)? selected-- : selected=opts.size()-1  ;
            mvwprintw(_menu, s.height-s.y_space*(selected+1), s.x_offset, ">");

            break;
          case 'A':
            mvwprintw(_menu, s.height- s.y_space*(selected+1), s.x_offset," ");
            selected=(selected+1)%opts.size();
            mvwprintw(_menu, s.height- s.y_space*(selected+1), s.x_offset, ">");

            break;
        }
        wattroff(_menu, COLOR_PAIR(s.color2));
        move(0,0);
        wrefresh(_menu);
      }
    }
  }


  






  inline std::ostream& operator<<(std::ostream& o, const settings& s){// only used for debbuging the default variables
    return (o<<"height : "<< s.height <<"\t width : "<<s.width);
  }





}

