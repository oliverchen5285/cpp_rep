#include "collision_detect3_base.h"

class collision_detect3_qt: public collision_detect3_base{
  Rect bound;
  vector<QuadTree> children;
  vector<Rect> rects;
  
  vector<Rect> splitBound();
  
  vector<vector<Rect>> quadRects(vector<Rect> new_bounds);
  
  bool operator< (Rect a, Rect b);
  
  int search_index(Rect rect);
  
  vector<pair<int, int>> re_index(vector<pair<int, int>> child_intersections, vector<Rect> child_rects);
  
  collision_detect3_qt(Rect new_bound, vector<Rect> new_rects): collision_detect3_base(new_rects);
  
  vector<pair<int, int>> intersections(int depth);
};
