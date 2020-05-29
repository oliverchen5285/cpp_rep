
#include "cd3_base.h"

bool cd3_base::collide_1d(const pair<int, int> &l1, const pair<int, int> &l2){
    //if both start before the other end
    return l1.first < l2.second && l2.first < l1.second;
}

bool cd3_base::collide_2d(const Rect &a, const Rect &b){
  return collide_1d({a.x, a.x2}, {b.x, b.x2}) && collide_1d({a.y, a.y2},{b.y, b.y2});
}


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
/*
cd3_base::cd3_base(vector<Rect> new_rects){
  rects = new_rects;
}
*/
void cd3_base::add_rect(const Rect &rect){
  rects.push_back(rect);
}

void cd3_base::clear_rects(){
  rects.clear();
}

