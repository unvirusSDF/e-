#include "../../include/imports.hpp"

namespace epp {
  

  action* actions;

  void init_act(void){
    actions = new action[10];

    actions[def_act::atk_base]=[](entity& e1, entity& e2){
      e2.stat.pv-=(int) (1.5* (double) e1.stat.atk)*(1-1/sqrt(e1.stat.def));
    };

    actions[atk_bdf]=[](entity& e1, entity& e2){
      e2.stat.pv/=2;
      if(!rand(0,2)) e1.stat.pv-=5;
    };

    actions[skip]=[](entity& e1, entity& e2){

    };

  }

  void end_act(void){
    delete actions;
  }

  action get_act(def_act act){
    return actions[act];  
  }


}
