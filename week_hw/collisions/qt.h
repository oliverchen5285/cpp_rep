#pragma once
#include "cd3_base.h"

//derived quad tree class from base class
class cd3_qt : public cd3_base{
public:
  Rect bound; //Rect representing boundary of all rects
  vector<cd3_qt> children; //vector of instances representing 1 quarter of quad tree
  
  vector<Rect> splitBound(); //helper function to return quadtree of bound
  
  vector<vector<Rect>> quadRects(vector<Rect> new_bounds); //helper function to return vector of Rects for every quarter
  
  int search_index(Rect rect); //helper function to search for Rect index
  
  vector<pair<int, int>> re_index(vector<pair<int, int>> child_intersections, vector<Rect> child_rects); //helper function to re-indexe rects (from quadRects vector to rects vector)
  
  vector<pair<int, int>> intersections(int depth); //returns vector of Rect intersections by recursively creating quad trees
};
//#endif
