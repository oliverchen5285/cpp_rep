#pragma once
#include "cd3_base.h"

//derived bf class from base class
class cd3_bf: public cd3_base{
public:
  vector<pair<int, int>> intersections(); //returns vector of Rect intersections
};
//#endif
