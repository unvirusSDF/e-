#include "../../include/imports.hpp"

namespace epp {

  tree<action> actions(1);

  void init_act(void){
    actions = tree<action>(10);

    actions.at(def_act::atk_base).__data()=[](entity& e1, entity& e2){
      e2.stat.pv-=(int) (1.5* (double) e1.stat.atk)*(1-1/sqrt(e1.stat.def));
    };

    actions.at(atk_bdf).__data()=[](entity& e1, entity& e2){
      e2.stat.pv/=2;
      if(!rand(0,2)) e1.stat.pv-=5;
    };

    actions.at(skip).__data()=[](entity& e1, entity& e2){

    };

  }

  action get_act(def_act act){
    return actions.at(act).__data();  
  }


}
