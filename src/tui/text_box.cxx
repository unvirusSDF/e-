#include "../../include/imports.hpp"

namespace epp {

  text_box::text_box(short int h, short int w, short int y, short int x, bool boxed)
  :s{boxed,h,w,y,x,boxed,1}{
    if(h){
      this->content = new char[h*(w+1)];
      std::fill(this->content, this->content+h*w,' ');
      for (short int i = 1; i < h; i++) {
        this->content[(i+1)*(w+1)-1]=NULL;
      }
    } 
  }

  text_box::~text_box(){
    if (this->s.height) delete this->content;
  }

  void text_box::operator()(){
    WINDOW* _text =((this->s.boxed)? newwin(this->s.height+1, this->s.width+1, this->s.pos_y, this->s.pos_x-1) :newwin(this->s.height, this->s.width, this->s.pos_y, this->s.pos_x));

    if(this->s.boxed) box(_text,0,0);

    wattron(_text, COLOR_PAIR(4));
    for (short int i = 1; i < this->s.height; i++) {
      mvwprintw(_text, this->s.y_space*(i), this->s.x_offset, this->content+(i*this->s.width+1)-1);
    }
    wattroff(_text,COLOR_PAIR(4));

    if(this->s.boxed) box(_text,0,0);

    wattron(_text, COLOR_PAIR(3));
    mvwprintw(_text, 0, 0, this->content);
    wattroff(_text, COLOR_PAIR(3));

    move(0,0);
    wrefresh(_text);

  }

  void text_box::_(){
    WINDOW* debug = newwin(this->s.height,this->s.width+1,10,35);
    box(debug,0,0);
    wrefresh(debug);
    int j=-1;
    for (short int i = 0; i < (this->s.width+1); i++) {
      for (short int  j = 0; j < this->s.height; j++) { 
        mvprintw(j+10,i+35,"%c",this->content[(this->s.width+1)*j+i]);
      }
    }
    refresh();
  }

  void text_box::line(short int l, char text[]){
    if (l<this->s.height){
      for (short int i = 0; i < this->s.width; i++) {
        this->content[l*(this->s.width)+i]=((text[i])? text[i] : NULL );
      }
      this->content[(l+1)*(this->s.width)-1]=NULL;
    }
  }

  short int& text_box::__x(){
    return this->s.pos_x;
  }

  short int& text_box::__y(){
    return this->s.pos_y;
  }
  short int& text_box::__h(){
    return this->s.height;
  }
  short int& text_box::__w(){
    return this->s.width;
  }
  char* text_box::__line(const short int i){
    return &(this->content[i*this->s.width+1]);
  }
}
