#pragma once 

#include <fstream>
#include <sstream>
#include <cstdint>

namespace epp {

  template<typename T>
  class node{
    public:
      node(T data = NULL, uint8_t size=0);
      ~node();

      void _free();

      T& __data();

      void operator delete(void*);

    private:
      T data;
      uint8_t child_num{0}; //replace all childs by children but do it in your head pls, I don't want to have uselessly long variable name
      uint8_t* child{nullptr};
  };

  template<typename T>
  class tree {
    public:
      tree(uint8_t size=0);
      ~tree();
      tree& operator=(tree&);
      tree& operator=(tree&&);

      uint8_t _head();
      uint8_t& __head();

      node<T>& get_head();
      node<T>& at(uint8_t);

    private:
      uint8_t size;
      node<T>* nodes{nullptr};
      uint8_t head;
  };
}

namespace epp {
  
  template<typename T>
  node<T>::node(T data, uint8_t size)
  :data{data}, child_num{size}{
    if(size!=0) new uint8_t[size];
  }

  template<typename T>
  void node<T>::_free(){
    if (this->child_num) delete this->child;
  }

  template<typename T>
  T& node<T>::__data(){
    return this->data;
  }


  template<typename T>
  node<T>::~node(){
    this->_free();
  }

  template<typename T>
  void node<T>::operator delete(void* e){
    (static_cast<node*>(e))->_free();
    ::delete static_cast<node*>(e);
  }


  template<typename T>
  tree<T>::tree(uint8_t size)
  :size{size}, nodes{new node<T>[size]}{
    for (uint8_t i = 0; i < size; this->nodes[i++]=node<T>());
  }

  template<typename T>
  tree<T>::~tree(){
    delete[] nodes;
  }

  template<typename T>
  node<T>& tree<T>::at(uint8_t i){
    if(i<this->size){
      return (this->nodes[i]);
    }
    std::cerr<<"tree nodes data accessed at index "<<i<<"\nbut max index allowed is"<<this->size<<'\n';
    endwin();
    exit(EXIT_FAILURE);
  }


  template<typename T>
  tree<T>& tree<T>::operator=(tree& t){
    std::swap(this->nodes, t.nodes);
    std::swap(this->head, t.head);
    std::swap(this->size, t.size);
    return *this;
  }

  template<typename T>
  tree<T>& tree<T>::operator=(tree&& t){
    std::swap(this->nodes, t.nodes);
    std::swap(this->head, t.head);
    std::swap(this->size, t.size);
    return *this;
  }

  template<typename T>
  uint8_t tree<T>::_head(){
    return this->head;
  }

  template<typename T>
  uint8_t& tree<T>::__head(){
    return this->head;
  }

  template<typename T>
  node<T>& tree<T>::get_head(){
    return this->nodes[this->head];
  }

}
