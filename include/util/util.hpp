#pragma once 

#include <fstream>
#include <sstream>
#include <cstdint>

namespace epp {

  template<typename T>
  struct tree<T> {
    uint8_t child_num;
    tree<T>* data;
  };



}
