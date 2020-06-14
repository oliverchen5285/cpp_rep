#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <utility>
#include <map>
#include <algorithm>
#include <fstream>
#include <chrono>
using namespace std;
using namespace std::chrono;

//base/parent class cd3_base
class cd3_base{
public:
  struct Rect{//Rect struct defined in class
    int x, y, x2, y2;
  };
  
  void add_rect(const Rect &rect); //adds Rect to rects vector

  void clear_rects(); //clears rects vector
  
  bool collide_1d(const pair<int, int> &l1, const pair<int, int> &l2); //helper function calculating 2 lines intersections

  bool collide_2d(const Rect &a, const Rect &b);  //helper function calculating 2 Rects intersections

  bool compare_Rect(const Rect &a, const Rect &b); //helper function comparing elements in Rect structs

  vector<Rect> rects; //vector of Rects

  vector<pair<int, int>> intersections_bf(); //returns vector of Rect intersections
  
};

