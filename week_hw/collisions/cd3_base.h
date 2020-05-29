#ifndef __CD3_BASE_H__
#define __CD3_BASE_H__

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

class cd3_base{
public:
  struct Rect{
    int x, y, x2, y2;
  };
  
  //cd3_base(vector<Rect> new_rects);

  void add_rect(const Rect &rect);

  void clear_rects();
  
  bool collide_1d(const pair<int, int> &l1, const pair<int, int> &l2);

  bool collide_2d(const Rect &a, const Rect &b);

  vector<Rect> rects;

  vector<pair<int, int>> intersections_bf();
  
private:
  
};

#endif

