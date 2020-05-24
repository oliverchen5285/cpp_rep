#include "collision_detect3_sh.h"

pair<int, int> collision_detect3_sh::zoneForPoint(const pair<int, int> &pt, const int &zsize){
  return {pt.first / zsize, pt.second / zsize};
}

vector<pair<int, int>> collision_detect3_sh::zoneForRect(const Rect &rect, int zsize){
  vector<pair<int, int>> zones;

  const pair<int, int> bl_zone = zoneForPoint({rect.x, rect.y}, zsize);
  const pair<int, int> ur_zone = zoneForPoint({rect.x2, rect.y2}, zsize);

  for(int i = bl_zone.first; i <= ur_zone.first; ++i){
    for(int j = bl_zone.second; j <= ur_zone.second; ++j){
      zones.push_back({i, j});
    }
  }
  return zones;
}

collision_detect3_sh::collision_detect3_sh(int zsize, vector<Rect> rects): collision_detect3_base(rects){
  
}

vector<pair<int, int>> collision_detect3_sh::intersections(){
  map<pair<int, int>, vector<int>> buckets;
     
  for(int i = 0; i < rects.size(); ++i){
    for(const auto &elem: zoneForRect(rects[i], zsize)){
      buckets[elem].push_back(i);
    }
  }
     
  set<pair<int, int>> intersections_set;

  for(const auto &elem: buckets){
    const vector<int> &rinds = elem.second;
    for(int i = 0; i < rinds.size(); ++i){
      for(int j = i + 1; j < rinds.size(); ++j){
        if(collide_2d(rects[rinds[i]], rects[rinds[j]])){
          intersections_set.insert({i, j});
        }
      }
    }
  }

  vector<pair<int, int>> intersections_vec;
  for(const auto &elem: intersections_set){
    intersections_vec.push_back(elem);
  }
  return intersections_vec;
}


