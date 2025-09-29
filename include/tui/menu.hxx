#pragma once

#include "./rendering.hxx"

namespace epp {
  
  struct settings{
    
    //settings();
    //explicit settings(bool boxed{false}, short int width{20}, short int height{20}, short int pos_x{0}, short int pos_y{0}, short int x_offset{1}, short int y_space{1});

    bool boxed {false};

    short int height{20};
    short int width{20};

    short int pos_y{0};
    short int pos_x{0};

    short int x_offset{1};
    short int y_space{1};
  };

  void init(settings&);
  inline std::ostream& operator<<(std::ostream&, const settings& s);

  typedef std::pair<char*, void (*)(void)> menu_opts;

  class menu {
    public:
      inline menu(std::vector<menu_opts>);
      menu(std::vector<menu_opts>, settings&, bool is_main);
      inline ~menu();

      void operator()();
      void _();

    private:
      bool is_main{false};
      short int opt_n;
      short int selected{opt_n};
      settings s{.boxed=0,.height=20,.width=20,.pos_y=0,.pos_x=0,.x_offset=2,.y_space=5};
      char selector[2]{'>',NULL};
      std::vector<std::pair<char*,void (*)(void)>> opts;

  };

  class text_box {
    public:
      text_box(short int h=0, short int w=0, short int y=0, short int x=0, bool boxed=true);
      text_box(text_box &&) = default;
      text_box(const text_box &) = default;
      text_box &operator=(text_box &&) = default;
      text_box &operator=(const text_box &) = default;
      ~text_box();

      void operator()();

      void _();

      void line(short int i, char text[]);


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
