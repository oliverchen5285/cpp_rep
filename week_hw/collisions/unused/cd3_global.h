#ifndef __CD3_GLOBAL_H__
#define __CD3_GLOBAL_H__
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


struct Rect{
  //changed rectangle parameters
  int x, y, x2, y2;
};

bool collide_1d(const pair<int, int> &l1, const pair<int, int> &l2){
    //if both start before the other end
    return l1.first < l2.second && l2.first < l1.second;
}

bool collide_2d(const Rect &a, const Rect &b){
  return collide_1d({a.x, a.x2}, {b.x, b.x2}) && collide_1d({a.y, a.y2},{b.y, b.y2});
}

class RectangleCollider_BF{
  private:
    vector<Rect> rects;
  public:
    void add(const Rect &rect){
      rects.push_back(rect);
    }
    
    void clear_rects(){
        rects.clear();
    }

    vector<pair<int, int>> intersections_bf(){
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
};

class RectangleCollider_SH{
  private:
    vector<Rect> rects;
    int zsize;
    
    pair<int, int> zoneForPoint(const pair<int, int> &pt, const int &zsize){
      return {pt.first / zsize, pt.second / zsize};
    }

    vector<pair<int, int>> zoneForRect(const Rect &rect, int zsize){
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
    
  public:
    void add(const Rect &rect){
      rects.push_back(rect);
    }
    
    void clear_rects(){
        rects.clear();
    }
    
    void setzsize(const int &x){
        zsize = x;
    }

    vector<pair<int, int>> intersections_sh(){
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
    
      vector<pair<int, int>> intersections;
      for(const auto &elem: intersections_set){
        intersections.push_back(elem);
      }
      return intersections;
    }
};

class QuadTree{
private:
    Rect bound;
    vector<QuadTree> children;
    vector<Rect> rects;
    
    vector<pair<int, int>> bf_intersections(){
        vector<pair<int, int>> intersections_vec;
        for(int i = 0; i < rects.size(); ++i){
            for(int j = i + 1; j < rects.size(); ++j){
                if(collide_2d(rects[i], rects[j])){
                    intersections_vec.push_back({rects[i], rects[j]});
                }
            }
        }
        return intersections_vec;
    }
    
    vector<Rect> splitBound(){
        vector<Rect> new_bounds;
        vector<vector<int, int>> apply_div = {
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
    
    vector<vector<Rect>> quadRects(vector<Rect> new_bounds){
        vector<vector<Rect>> quad_rect_vec;
        for(const auto &elem: new_bounds){
            vector<int> temp_vec;
            for(const auto &elem2: rects){
                if(collide_2d(elem, elem2)){
                    temp_vec.push_back(elem2);
                }
            }
            quad_rect_vec.push_back(temp_vec);
        }
        return quad_rect_vec;
    }
    
    bool operator< (Rect a, Rect b){ //comparator for using Rect as map key
        return a.x < b.x; //I don't think the comparator will matter...
    }
    
    int search_index(Rect rect){
        for(int i = 0; i < rects.size(); ++i){
            if(rect == rects[i]){
                return i;
            }
        }
        return -1;
    }
    
    vector<pair<int, int>> re_index(vector<pair<int, int>> child_intersections, vector<Rect> child_rects){
        vector<pair<int, int>> new_index_vec;
        //asumming no duplicate rectangles
        map<Rect, int> rect_to_index; //maps child rects to parent indexes
        for(const auto &elem: child_intersections){
            pair<int, int> temp_intersection;
            if(rect_to_index.find(child_rects[elem.first]) != rect_to_index.end()){ //if key already created
                temp_intersection.first == rect_to_index[child_rects[elem.first]];
            }
            else{
                rect_to_index[child_rects[elem.first]] == search_index(child_rects[elem.first]);
                temp_intersection.first == rect_to_index[child_rects[elem.first]];
            }
            if(rect_to_index.find(child_rects[elem.second]) != rect_to_index.end()){ //if key already created
                temp_intersection.second == rect_to_index[child_rects[elem.second]];
            }
            else{
                rect_to_index[child_rects[elem.second]] == search_index(child_rects[elem.second]);
                temp_intersection.second == rect_to_index[child_rects[elem.second]];
            }
            new_index_vec.push_back(temp_intersection);
            
        }
        return new_index_vec;
    }
public:
    QuadTree(Rect new_bound, vector<Rect> new_rects){
        bound = new_bound;
        rects = new_rects;
    }
    
    void clear_rects(){
        rects.clear();
    }
    
    vector<pair<int, int>> intersections(int depth){
        if(rects.size() >= 8 || depth <= 0){
            return bf_intersections();
        }
        //else split into quad trees
        
        vector<Rect> new_bounds = splitBound();
        vector<vector<Rect>> quad_rect_vec = quadRects(new_bounds);
        
        set<pair<int, int>> remove_dup;
        
        for(int i = 0; i < 4; ++i){
            QuadTree child(new_bounds[i], quad_rect_vec[i]);
            vector<pair<int, int>> child_intersections = child.intersections(depth - 1);
            vector<pair<int, int>> new_index_vec = re_index(child_intersections, quad_rect_vec[i]);
            for(const auto &elem: new_index_vec){
                remove_dup.push_back(elem);
            }
            children.push_back(child);
        }
        
        vector<pair<int, int>> intersections_vec;
        for(const auto &elem: remove_dup){
            intersections_vec.push_back(elem);
        }
        return intersections_vec;
    }
};



int main(){

  RectangleCollider_BF rectcolbf;
  RectangleCollider_SH rectcolsh;
  
  QuadTree rectcolqt;

  ifstream fin("rect_cases.txt");  

  int case_num;
  fin >> case_num;

  for(int i = 0; i < case_num; ++i){
      Rect bound;
      fin >> bound.x >> bound.y >> bound.x2 >> bound.y2;
      if(bound.x2 %2 != 0){
          bound.x2 += 1;
      }
      if(bound.y2 %2 != 0){
          bound.y2 += 1;
      }
      int rect_num;
      fin >> rect_num;
      rectcolbf.clear_rects();
      rectcolsh.clear_rects();
      vector<Rect> temp_rects;
      for(int j = 0; j < rect_num; ++j){
          Rect rect;
          fin >> rect.x >> rect.y >> rect.x2 >> rect.y2;
          rectcolbf.add(rect);
          rectcolsh.add(rect);
          temp_rects.push_back(rect);
      }
      rectcolsh.setzsize(75);
      
      auto start_time = high_resolution_clock::now();
      cout << rectcolbf.intersections_bf().size();
      auto stop_time = high_resolution_clock::now();
      auto duration = duration_cast<microseconds>(stop_time - start_time);
      cout << ", " << duration.count() << endl;
      
      start_time = high_resolution_clock::now();
      cout << rectcolsh.intersections_sh().size();
      stop_time = high_resolution_clock::now();
      duration = duration_cast<microseconds>(stop_time - start_time);
      cout << ", " << duration.count() << endl;
      
      QuadTree rectcolqt(bound, temp_rects);
      
      start_time = high_resolution_clock::now();
      cout << rectcolqt.intersections(1).size();
      stop_time = high_resolution_clock::now();
      duration = duration_cast<microseconds>(stop_time - start_time);
      cout << ", " << duration.count() << endl;
      
      cout << endl;
      
  }  


}
#endif
