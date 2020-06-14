#include "cd3_base.h"

//helper function for collide_2d (returns if 2 lines intersect)
bool cd3_base::collide_1d(const pair<int, int> &l1, const pair<int, int> &l2){
    //if both start before the other end
    return l1.first < l2.second && l2.first < l1.second;
}

//helper function to check if 2 rectangles intersect
bool cd3_base::collide_2d(const Rect &a, const Rect &b){
  return collide_1d({a.x, a.x2}, {b.x, b.x2}) && collide_1d({a.y, a.y2},{b.y, b.y2});
}

//helper function to see if all elements of 2 Rect structs are equal
bool cd3_base::compare_Rect(const Rect &a, const Rect &b){
  return a.x == b.x && a.y == b.y && a.x2 == b.x2 && a.y2 == b.y2;
}

//returns vector of Rect intersections using brute force
vector<pair<int, int>> cd3_base::intersections_bf(){
  vector<pair<int, int>> intersections;
  for(int i = 0; i < rects.size(); ++i){
    for(int j = i + 1; j < rects.size(); ++j){
      if(collide_2d(rects[i], rects[j])){
        intersections.push_back({i, j});
      }
    }
  }
  return intersections;
}

//function to help initialize rects vector
void cd3_base::add_rect(const Rect &rect){
  rects.push_back(rect);
}

//function to help clear rects vector
void cd3_base::clear_rects(){
  rects.clear();
}

