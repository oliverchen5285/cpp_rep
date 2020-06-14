#pragma once
#include "cd3_base.h"

//derived sh class from base class
class cd3_sh: public cd3_base{
public:
  int zsize; //size of zones to divide bounds into

  pair<int, int> zoneForPoint(const pair<int, int> &pt, const int &zsize); //helper function to calculate zone for point

  vector<pair<int, int>> zoneForRect(const Rect &rect, int zsize); //helper function to calculate zone(s) for Rect

  vector<pair<int, int>> intersections(); //returns vector of Rect intersections using spacial hash

};
