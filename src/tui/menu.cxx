#include "../../include/imports.hpp"

namespace epp {
  
  inline void rst_scr(short int y, short int x, short int h, short int w){
    if((x==0)||(y==0)) getmaxyx(stdscr,h,w); 
    WINDOW* win = newwin(h, w,y,x); //reset the screen
    wrefresh(win);
  }

  inline menu::menu(std::vector<menu_opts> opts,):
    selected {0}, selector{">"}, opt_n { (short int) opts.size()}//, s{.boxed=0,.height=20,.width=20,.pos_y=0,.pos_x=0,.x_offset=2,.y_space=5} 
  {
    this->s.pos_y=0;
    this->s.pos_x=0;
    this->opts=opts;
    getmaxyx(stdscr, this->s.height, this->s.width);
  }

  menu::menu(std::vector<menu_opts> opts, settings& set, bool is_main):
    selected {0}, opt_n { (short int) opts.size()}, s{set}, is_main{is_main}
  {
    this->opts=opts;
    getmaxyx(stdscr, this->s.height, this->s.width);
  }
 
  inline menu::~menu(){

  }

  void menu::operator()(){

    WINDOW* _menu = newwin(this->s.height, this->s.width, this->s.pos_y, this->s.pos_x);

    if(this->s.boxed) box(_menu,0,0);

    wattron(_menu, COLOR_PAIR(1));
    for (short int i = 0; i < this->opt_n; i++) {
      mvwprintw(_menu, this->s.height- this->s.y_space*(i+1),this->s.x_offset+1, this->opts.at(i).first);
    }
    wattroff(_menu,COLOR_PAIR(1));
    this->selected=this->opt_n-1;
    wattron(_menu, COLOR_PAIR(2));
    mvwprintw(_menu,this->s.height- this->s.y_space*(selected+1),this->s.x_offset, this->selector);
    wattroff(_menu, COLOR_PAIR(2));
    move(0,0);
    wrefresh(_menu);


    while (1) {
      //get user input
      noecho();
      const char c = getch();
      if (c=='\n'){ // if enter pressed == "I choose it"
        for (short int i = 0; i < this->opt_n ; i++) {
          if (i==this->selected){
            this->opts.at(i).second(); //execute the function associated with the coice selected
            break;
          }
        }
        if(!is_main) break;
        //run only if its a main menu
        //redraw the interface just in case
        if(this->s.boxed) box(_menu,0,0);

        wattron(_menu, COLOR_PAIR(1));
        for (short int i = 0; i < this->opt_n; i++) {
          mvwprintw(_menu, this->s.height- this->s.y_space*(i+1),this->s.x_offset+1, this->opts.at(i).first);
        }
        wattroff(_menu,COLOR_PAIR(1));
        this->selected=this->opt_n-1;
        wattron(_menu, COLOR_PAIR(2));
        mvwprintw(_menu,this->s.height- this->s.y_space*(selected+1),this->s.x_offset, this->selector);
        wattroff(_menu, COLOR_PAIR(2));
        move(0,0);
        wrefresh(_menu);

      }

      //let's do the frontend and the choice selection
  
      if ((c=='\x1b')&&(getch()=='[')) { //escape sequence + char corresponding to the arrows
        wattron(_menu, COLOR_PAIR(2));
        switch (getch()) {
          case 'B':
            mvwprintw(_menu,this->s.height- this->s.y_space*(selected+1),this->s.x_offset," ");
            (selected)? selected-- : selected=opt_n-1  ;
            mvwprintw(_menu,this->s.height- this->s.y_space*(selected+1),this->s.x_offset, this->selector);

            break;
          case 'A':
            mvwprintw(_menu,this->s.height- this->s.y_space*(selected+1),this->s.x_offset," ");
            selected=(selected+1)%opt_n;
            mvwprintw(_menu,this->s.height- this->s.y_space*(selected+1),this->s.x_offset, this->selector);

            break;
        }
        wattroff(_menu, COLOR_PAIR(2));
        move(0,0);
        wrefresh(_menu);
      }
    }
  }



  void menu::_(){
    mvprintw(2,2,"i exist");
    mvprintw(3,2,"boxed    : %s", (this->s.boxed)? "true" : "false");
    mvprintw(4,2,"height   : %i", this->s.height);
    mvprintw(5,2,"width    : %i", this->s.width);
    mvprintw(6,2,"pos y    : %i", this->s.pos_y);
    mvprintw(7,2,"pos x    : %i", this->s.pos_x);
    mvprintw(8,2,"x_offset : %i", this->s.x_offset);
    mvprintw(9,2,"y_space  : %i", this->s.y_space);
    mvprintw(6,2,"selector : \'%s\'", this->selector);
  }
  




  /*
  settings::settings(bool boxed, short int width, short int height, short int pos_x, short int pos_y, short int x_offset, short int y_space){
    getmaxyx(stdscr, this->height, this->width);
  }*/

  inline std::ostream& operator<<(std::ostream& o, const settings& s){
    return (o<<"height : "<< s.height <<"\t width : "<<s.width);
  }





}

