#include "../../include/imports.hpp"

/*
namespace epp {

  template<typename T>
  tree<T>::tree<T>(){

  }


  template<typename T>
  tree<T>::~tree<T>(){
    for (uint8_t i = 0; i < this->child_num; delete this->data[i++]);
    ::delete this->data;
  }


  template<typename T>
  void tree<T>::operator delete(void* e){
    if(static_cast<tree<T>*>(e)->child_num){
      for (uint8_t i = 0; i < static_cast<tree<T>*>(e)->child_num; delete static_cast<tree<T>*>(e)->data[i++]);
    }
    ::delete static_cast<tree*>(e)->data;
    ::delete static_cast<tree*>(e);
  }

}*/
