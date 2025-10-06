#pragma once

namespace epp {
  void main_bis();

  void loose(void);
  void win(void);

  struct stats {
    int pv;

    int atk, def;

  };

  enum def_act {
    skip=0, atk_base=1, atk_bdf=2,
  };

  class entity {
    public:
      entity(int pv=100, int atk=10, int def =10);
      entity(entity &&) = default;
      entity(const entity &) = default;
      entity &operator=(entity &&) = default;
      entity &operator=(const entity &) = default;
      ~entity();

      entity& operator()(def_act, entity&);
      void die(void);
    
    
      stats stat;
      size_t xp;
  };



  using action = void(*)(entity&,entity&);

  action get_act(def_act);

  void init_act(void);

}
