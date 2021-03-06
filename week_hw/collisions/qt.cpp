#include "cd3_qt.h"

//helper function to split bound into quadtree  
vector<cd3_base::Rect> cd3_qt::splitBound(){
  vector<Rect> new_bounds;
  vector<vector<int>> apply_div = {
    {bound.x, bound.y, (bound.x + bound.x2)/2, (bound.y + bound.y2)/2},
    {bound.x, (bound.y + bound.y2)/2, (bound.x + bound.x2)/2, bound.y2},
    {(bound.x + bound.x2)/2, bound.y, bound.x2, (bound.y + bound.y2)/2},
    {(bound.x + bound.x2)/2, (bound.y + bound.y2)/2, bound.x2, bound.y2} };
  for(const auto &elem: apply_div){
    Rect temp_rect;
    temp_rect.x = elem[0]; temp_rect.y = elem[1]; temp_rect.x2 = elem[2]; temp_rect.y2 = elem[3];
    new_bounds.push_back(temp_rect);
  }
  return new_bounds;
}

//helper function to place Rects into each quad
vector<vector<cd3_base::Rect>> cd3_qt::quadRects(vector<Rect> new_bounds){
  vector<vector<Rect>> quad_rect_vec;
  for(const auto &elem: new_bounds){
    vector<Rect> temp_vec;
    for(const auto &elem2: rects){
      if(collide_2d(elem, elem2)){
        temp_vec.push_back(elem2);
      }
    }
    quad_rect_vec.push_back(temp_vec);
  }
  return quad_rect_vec;
}

//helper function to return index of Rect
int cd3_qt::search_index (Rect rect){
  for(int i = 0; i < rects.size(); ++i){
    if(compare_Rect(rect,rects[i])){
      return i;
    }
  }
  return -1;
}

//helper function to re-index Rects from child_intersections to rects
vector<pair<int, int>> cd3_qt::re_index(vector<pair<int, int>> child_intersections, vector<Rect> child_rects){
  vector<pair<int, int>> new_index_vec;
  
  map<int, int> child_parent;
  for(const auto &elem: child_intersections){
    pair<int, int> temp_intersection;
    if((child_parent.find(elem.first)) != child_parent.end()){ //key already created
      temp_intersection.first = child_parent[elem.first];
    }
    else{
      child_parent[elem.first] = search_index(child_rects[elem.first]);
      temp_intersection.first = child_parent[elem.first];
    }
    if((child_parent.find(elem.second)) != child_parent.end()){ //key already created
      temp_intersection.second = child_parent[elem.second];
    }
    else{
      child_parent[elem.second] = search_index(child_rects[elem.second]);
      temp_intersection.second = child_parent[elem.second];
    }
    new_index_vec.push_back(temp_intersection);
  }
  return new_index_vec;
}

//returns vector of Rect intersections by recursively creating quadtrees
vector<pair<int, int>> cd3_qt::intersections(int depth){
  if(rects.size() >= 8 || depth <= 0){
    return intersections_bf();
  }
  //else split into quad trees
  
  vector<Rect> new_bounds = splitBound();
  vector<vector<Rect>> quad_rect_vec = quadRects(new_bounds);
  
  set<pair<int, int>> remove_dup;
  
  for(int i = 0; i < 4; ++i){
    cd3_qt child;
    child.bound = new_bounds[i];
    child.rects = quad_rect_vec[i];
    //cd3_qt child(new_bounds[i], quad_rect_vec[i]);
    vector<pair<int, int>> child_intersections = child.intersections(depth - 1);
    vector<pair<int, int>> new_index_vec = re_index(child_intersections, quad_rect_vec[i]);
    for(const auto &elem: new_index_vec){
      remove_dup.insert(elem);
    }
    children.push_back(child);
  }
  
  vector<pair<int, int>> intersections_vec;
  for(const auto &elem: remove_dup){
    intersections_vec.push_back(elem);
  }
  return intersections_vec;
}
