#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <utility>
#include <map>
#include <chrono>
using namespace std;
using namespace std::chrono;


struct Rect{
  //changed rectangle parameters
  int x, y, x2, y2;
};


class RectangleCollider{
  private:
    vector<Rect> rects;

    bool collide_1d(const pair<int, int> &l1, const pair<int, int> &l2){
      return (l1.first >= l2.first && l1.first < l2.second) || (l1.second <= l2.second && l1.second > l2.first) || (l2.first >= l1.first && l2.first < l1.second) || (l2.second <= l1.second && l2.second > l1.first);
    }
    bool collide_2d(const Rect &a, const Rect &b){
      return collide_1d({a.x, a.x2}, {b.x, b.x2}) && collide_1d({a.y, a.y2},{b.y, b.y2});
      /*
      if(a.x < b.x){
        //a left side of b
        if(a.y < b.y){
          //a top side of b
          return a.x2 > b.x && a.y < b.y2;
        }
        else{
          //a lower side of or equal to b
          return a.x2 > b.x && a.y2 > b.y;
        }
      }
      else{
        //a right side of or equal to b
        if(a.y < b.y){
          //a top side of b
          return a.x < b.x2 && a.y < b.y2;
        }
        else{
          //a lower side of or equal to b
          return a.x < b.x2 && a.y2 > b.y;
        }
      }
      */
    }

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

    vector<Rect> splitBounds(Rect bounds){
      vector<Rect> quadtree;

      Rect bound1 = bounds;
      bound1.x2 = bounds.x + (bounds.x2 - bounds.x)/2;
      bound1.y2 = bounds.y + (bounds.y2 - bounds.y)/2;

      Rect bound2 = bounds;
      bound2.x = bounds.x + (bounds.x2 - bounds.x)/2;
      bound2.y2 = bounds.y + (bounds.y2 - bounds.y)/2;

      Rect bound3 = bounds;
      bound3.y = bounds.y + (bounds.y2 - bounds.y)/2;
      bounds.x2 = bounds.x + (bounds.x2 - bounds.x)/2;
 
      Rect bound4 = bounds;
      bound4.x = bounds.x + (bounds.x2 - bounds.x)/2;
      bound4.y = bounds.y + (bounds.y2 - bounds.y)/2;

      quadtree.push_back(bound1);
      quadtree.push_back(bound2);
      quadtree.push_back(bound3);
      quadtree.push_back(bound4);
      return quadtree;
    }

    vector<vector<int>> groupsForQuad(const vector<Rect> rects_qg, Rect bounds){
      vector<vector<int>> quadgroups;
      for(int i = 0; i < 4; ++i){
        vector<int> temp;
        quadgroups.push_back(temp);
      }

      vector<Rect> newBounds = splitBounds(bounds);

      for(int i = 0; i < newBounds.size(); ++i){
        for(int j = 0; j < rects_qg.size(); ++j){
          if(collide_2d(newBounds[i], rects_qg[j])){
            quadgroups[i].push_back(j);
          }
        }
      }
      return quadgroups;
    }
    bool compareRect(const Rect &a, const Rect &b){
        return a.x == b.x && a.y == b.y && a.x2 == b.x2 && a.y2 == b.y2;
    }
  public:
    void add(const Rect &rect){
      rects.push_back(rect);
    }
    
    vector<Rect> ret_rects(){
      return rects;
    }    

    vector<pair<int, int>> intersections_bf(vector<Rect> rects_bf){
      vector<pair<int, int>> intersections;
      for(int i = 0; i < rects_bf.size(); ++i){
        for(int j = i + 1; j < rects_bf.size(); ++j){
          if(collide_2d(rects_bf[i], rects_bf[j])){
            intersections.push_back({i, j});
          }
        }
      }
      return intersections;
    }
    vector<pair<int, int>> intersections_sh(const int &zsize){
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
    vector<pair<int, int>> intersections_qt(int depth, Rect bounds, const vector<Rect> rects_qt){
      if(depth == 0 || rects_qt.size() <= 3){
        return intersections_bf(rects_qt);
      }

       vector<vector<int>> quadgroups = groupsForQuad(rects_qt, bounds);
       vector<Rect> newbounds = splitBounds(bounds);
       
       set<pair<int, int>> intersections_set;

       for(int i = 0; i < quadgroups.size(); ++i){
         vector<Rect> rect_quadgroups;
         for(int j = 0; j < quadgroups[i].size(); ++j){
           rect_quadgroups.push_back(rects_qt[quadgroups[i][j]]);
         }
         vector<pair<int, int>> quad_intersections = intersections_qt(depth - 1, newbounds[i], rect_quadgroups);
         for(const auto &elem: quad_intersections){
             int firstint = 0;
             for(int k = 0; k < rects_qt.size(); ++k){
                 if(compareRect(rects_qt[k], rect_quadgroups[elem.first])){
                     firstint = k;
                 }
             }
             int secondint = 0;
             for(int k = 0; k < rects_qt.size(); ++k){
                 if(compareRect(rects_qt[k], rect_quadgroups[elem.second])){
                     secondint = k;
                 }
             }
             intersections_set.insert({firstint, secondint});
         }
       }
     
      vector<pair<int, int>> intersections;
      for(const auto &elem: intersections_set){
        intersections.push_back(elem);
      }

      return intersections;
    }
};

int main(){
  RectangleCollider a;
  
  int n;
  cin >> n;
   
  for(int i = 0; i < n; ++i){
    Rect temprect;    
    cin >> temprect.x >> temprect.y;
    int w, h;
    cin >> w >> h;
    temprect.x2 = temprect.x + w;
    temprect.y2 = temprect.y + h;
 
    a.add(temprect);
  }

  auto start_time = high_resolution_clock::now();
  vector<pair<int, int>> ans = a.intersections_bf(a.ret_rects());
  auto stop_time = high_resolution_clock::now();

  auto duration = duration_cast<microseconds>(stop_time - start_time);

  cout << "bf ans: " << ans.size() << endl;
    for(int i = 0; i < ans.size(); ++i){
        cout << ans[i].first << ", " << ans[i].second << " -- ";
    }
    cout << endl;
  cout << "bf time: " << duration.count() << endl;

  start_time = high_resolution_clock::now();
  ans = a.intersections_sh(100);
  stop_time = high_resolution_clock::now();

  duration = duration_cast<microseconds>(stop_time - start_time);

  cout << "sh ans: " << ans.size() << endl;
  cout << "sh time: " << duration.count() << endl; 

  Rect bounds;
  bounds.x = 0; bounds.y = 0; bounds.x2 = 64; bounds.y2 = 64;

  start_time = high_resolution_clock::now();
  ans = a.intersections_qt(4, bounds, a.ret_rects());
  stop_time = high_resolution_clock::now();

  duration = duration_cast<microseconds>(stop_time - start_time);

  cout << "qt ans: " << ans.size() << endl;
    for(int i = 0; i < ans.size(); ++i){
        cout << ans[i].first << ", " << ans[i].second << " -- ";
    }
    cout << endl;
  cout << "qt time: " << duration.count() << endl;
}
