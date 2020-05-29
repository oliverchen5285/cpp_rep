#ifndef __CD3_QT_H__
#define __CD3_QT_H__
#include "cd3_base.h"

class cd3_qt: public cd3_base{
public:
  Rect bound;
  vector<cd3_qt> children;
  vector<Rect> rects;
  
  vector<Rect> splitBound();
  
  vector<vector<Rect>> quadRects(vector<Rect> new_bounds);
  
  //bool operator< (Rect a, Rect b);
  
  int search_index(Rect rect);
  
  vector<pair<int, int>> re_index(vector<pair<int, int>> child_intersections, vector<Rect> child_rects);
  
  //cd3_qt(Rect new_bound, vector<Rect> new_rects): cd3_base(new_rects), bound(new_bound){};
  
  vector<pair<int, int>> intersections(int depth);
};
#endif
