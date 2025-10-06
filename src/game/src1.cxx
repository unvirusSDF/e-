#include "../../include/imports.hpp"

namespace epp {

  void** shared_data = nullptr;

  void display_sd(){//display the enemy stat as well as the player stats
    short int H,W;
    getmaxyx(stdscr,H,W);
    //player
    entity e = * (entity*) shared_data[0];
    WINDOW* u = newwin(20,20,H-30, 50);


    wattron(u, COLOR_PAIR(5));
    mvwprintw(u,1,1,"pv  : \n\n atk : \n\n def : \n\n xp  : ");
    wattroff(u, COLOR_PAIR(5));

    mvwprintw(u,1,7,"%i", e.stat.pv);
    mvwprintw(u,3,7,"%i", e.stat.atk);
    mvwprintw(u,5,7,"%i", e.stat.def);
    mvwprintw(u,7,7,"%llu", e.xp);

    wattron(u, COLOR_PAIR(6));
    box(u,0,0);
    wattroff(u, COLOR_PAIR(6));

    wrefresh(u);

    //enemy
    e = * (entity*) shared_data[1];
    WINDOW* v = newwin(20,20,H-30, W-70);


    wattron(v, COLOR_PAIR(5));
    mvwprintw(v,1,1,"pv  : \n\n atk : \n\n def : ");
    wattroff(v, COLOR_PAIR(5));

    mvwprintw(v,1,7,"%i", e.stat.pv);
    mvwprintw(v,3,7,"%i", e.stat.atk);
    mvwprintw(v,5,7,"%i", e.stat.def);
    
    wattron(v, COLOR_PAIR(4));
    box(v,0,0);
    wattroff(v, COLOR_PAIR(4));

    wrefresh(v);
  }

  entity::entity(int pv, int atk, int def)
  :stat{pv,atk,def}, xp{0}{
  }

  entity::~entity(){

  }

  void entity::die(void){
    win();
  }

  entity& entity::operator()(def_act act, entity& e){

    //funfact : something like two days after it wrote this beatiful line, I read it and thought WTF
    //          after I just remembered how cursed it was but it works perfectly, so it's fine
    get_act(act)(*this, e); //do the action which match the enum type def_act
    // ^fuction pointer ^evaluated with *this and e as args

    char buf[80]="";
    sprintf(buf, "attack occurs, bro WTF you have %i pv and your opponent only got %i", this->stat.pv, e.stat.pv);
    buf[79]='\0';
    printlog(buf);

    display_sd();

    if(this->stat.pv<=0){
      loose();
    }

    if(e.stat.pv<=0){
      this->xp+=5;
      char buf[40]="";
      sprintf(buf, "congrats you won 5xp, you have %ixp now", this->xp);
      buf[38]='\0';
      printlog(buf);
      e.die();
    }
    return *this;

  }


  void loose(void){
    short int H,W;
    getmaxyx(stdscr,H,W);
    text_box looser(10,20,H/2 -5, W/2 -10,1,1,5);
    looser.line(0,"Haha, looser");
    looser.line(1,"I think that you");
    looser.line(2,"have some major ");
    looser.line(3,"skills issues");
    looser();
    getch();
    quit(2);
  }

  void win(void){
    short int H,W;
    getmaxyx(stdscr,H,W);
    text_box u(10,20,H/2 -5, W/2 -10,1,2,3);
    u.line(0,"congrats");
    u.line(1,"It seems that you  ");
    u.line(2,"won ,still I don't ");
    u.line(3,"understand how     ");
    u.line(4,"given your negative");
    u.line(5,"skills             ");
    u.line(9, "looser");
    u();
    getch();
    quit(2);
  }




  void main_bis(void){ // meant to be exported and executed elsewhere
    shared_data = new void*[2];
    init_act();
    short int H,W;
    getmaxyx(stdscr,H,W);
    rst_scr();
    entity player(100,10,10);

    entity enemy(100,10,10);

    shared_data[0]=&player;
    shared_data[1]=&enemy;

    display_sd();
    startlog();
    printlog("logs initalized");

    settings s{0,20,20,((short int) (H-20)),0,2,5,1,2};

    menu(std::vector<menu_opts>{
        menu_opts((char*) "quit all",[](void){rst_scr(); quit(10);}),
        menu_opts((char*) "quit", [](void){rst_scr(); quit();}),
        menu_opts((char*) "action",[](void){//open the action menu
            short int H,W;
            getmaxyx(stdscr,H,W);
            settings t{0,20,20,((short int) (H-20)),20,2,2,2,3};
            menu(std::vector<menu_opts>{
                menu_opts((char*) "back", [](void){quit();}),
                menu_opts((char*) "attack", [](void){(*(entity*) shared_data[0] )(def_act::atk_base,*(entity*) shared_data[1]);}),
                menu_opts((char*) "fire ball", [](void){(*(entity*) shared_data[0] )(def_act::atk_bdf,*(entity*) shared_data[1]);}),
                menu_opts((char*) "skip", [](void){(*(entity*) shared_data[0] )(def_act::skip,*(entity*) shared_data[1]);} )
              },t);
            rst_scr(20,20,H-20,20);//clean the action menu when quited
          })
    }, s);


    delete shared_data;
    endlog();
    rst_scr();

  }
}
