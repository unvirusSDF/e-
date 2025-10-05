#pragma once

#include <vector>

#include "./rendering.hxx"

namespace epp {
  
  struct settings{ // used by every printable so it's a struct, could also have been a macro
    
    //settings();
    //explicit settings(bool boxed{false}, short int width{20}, short int height{20}, short int pos_x{0}, short int pos_y{0}, short int x_offset{1}, short int y_space{1});

    bool boxed {false};

    short int height{20};
    short int width{20};

    short int pos_y{0};
    short int pos_x{0};

    short int x_offset{1};
    short int y_space{1};

    int color1{1};
    int color2{2};
  };

  inline std::ostream& operator<<(std::ostream&, const settings& s);// the print

  typedef std::pair<char*, void (*)(void)> menu_opts;// option as str and a lambda to run when the coice is selected

  void menu(std::vector<menu_opts>, settings&);
      
  class text_box {
    public:
      text_box(short int h=0, short int w=0, short int y=0, short int x=0, bool boxed=true, int color1=3, int color=4);
      text_box(text_box &&) = default;
      text_box(const text_box &) = default;
      text_box &operator=(text_box &&) = default;
      text_box &operator=(const text_box &) = default;
      ~text_box();

      void operator()();

      void _();

      void line(short int i, char text[]);

    //getters
      short int& __x();
      short int& __y();
      short int& __h();
      short int& __w();
      char* __line(const short int i=0);

    
    private:

      settings s;

      char* content{nullptr};
  };

}
