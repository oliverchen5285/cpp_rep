#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h> //srand
#include <utility>
#include <algorithm>
using namespace std;

struct Rect{
  int width, height;
  pair<int, int> pos;
  Rect(int new_width, int new_height, pair<int, int> new_pos = {-1, -1}){
    width = new_width;
    height = new_height;
    pos = new_pos;
  }
};


bool collide_1d(const pair<int, int> l1, const pair<int, int> l2){
  return l1.first < l2.second && l2.first < l1.second;
}

bool collide_2d(const Rect r1, const Rect r2){
  return collide_1d({r1.pos.first, r1.pos.first + r1.width}, {r2.pos.first, r2.pos.first + r2.width}) && collide_1d({r1.pos.second, r1.pos.second + r1.height}, {r2.pos.second, r2.pos.second + r2.height});
}

