// HEREEEEEE!!!
#include <algorithm>
#include <iostream>
#include <chrono>
#include <vector>
#include <set>
#include <unordered_map>
using namespace std;
using namespace std::chrono;

class Timer
{
public:
    Timer() : beg_(clock_::now()) {}
    void reset() { beg_ = clock_::now(); }
    double elapsed() const {
        return std::chrono::duration_cast<second_>
            (clock_::now() - beg_).count(); }

private:
    typedef std::chrono::high_resolution_clock clock_;
    typedef std::chrono::duration<double, std::ratio<1> > second_;
    std::chrono::time_point<clock_> beg_;
};

struct Rect {
  int x=-1,y=-1,w=-1,h=-1;
};
istream& operator>>(istream &in, Rect &r) {
  return (in >> r.x >> r.y >> r.w >> r.h);
}
ostream& operator<<(ostream &out, const Rect &r) {
  return (out << "R(" << r.x << "," << r.y << ":" << r.w << "x" << r.h << ")");
}

/*
vector<pair<int, int>> intersect_brute_force(const vector<Rect> &rects) {
  // ...
}
*/
bool collide_1d(int x1, int w1, int x2, int w2) {
  return (x1 + w1 > x2) && (x2 + w2 > x1);
}
bool collide_2d(const Rect &a, const Rect &b){
  if(a.x < b.x){
    //a left side of b
    if(a.y < b.y){
      //a top side of b
      return a.x + a.w > b.x && a.y < b.y + b.h;
    }
    else{
      //a lower side of or equal to b
      return a.x + a.w > b.x && a.y + a.h > b.y;
    }
  }
  else{
    //a right side of or equal to b
    if(a.y < b.y){
      //a top side of b
      return a.x < b.x + b.w && a.y < b.y + b.h;
    }
    else{
      //a lower side of or equal to b
      return a.x < b.x + b.w && a.y + a.h > b.y;
    }
  }
}

vector<pair<int, int> > count_collisions_bf(vector<Rect> &rects){
  vector<pair<int, int> > collisions;
  for(int i = 0; i < rects.size(); ++i){
    for(int j = i + 1; j < rects.size(); ++j){
      if(collide_2d(rects[i], rects[j])){
        collisions.push_back({i, j});
      }
    }
  }
  return collisions;
  
}

vector<pair<int, int> > count_collisions_2(vector<Rect> &rects){
  vector<Rect> bounds;
  for(int i = 0; i <= 80; i+= 20){
    for(int j = 0; j <= 80; j+= 20){
      Rect temp_rect;
      temp_rect.x = i;
      temp_rect.y = j;
      temp_rect.w = 20;
      temp_rect.h = 20;
      bounds.push_back(temp_rect);
    }
  }
  //assume bounds for now
  vector<pair<int, int> > collisions;
  
  //vector<vector<int> > rect_groups;
  unordered_map<int, vector<int> > rect_groups;
  /*
  for(int i = 0; i < bounds.size(); ++i){
    vector<int> temp_vec;
    rect_groups.push_back(temp_vec);
  }
  */

  for(int i = 0; i < rects.size(); ++i){
    for(int j = 0; j < bounds.size(); ++j){
      if(collide_2d(rects[i], bounds[j])){
        //rect_groups[j].push_back(i);
        if(rect_groups.find(j) != rect_groups.end()){
          rect_groups[j].push_back(i);
        }
        else{
          vector<int> temp;
          rect_groups[j] = temp;
          rect_groups[j].push_back(i);
        }
      }
    }
  }
  //removes duplicates
  set<pair<int, int> > col_set;
  for(auto &elem: rect_groups){
    for(int j = 0; j < elem.second.size(); ++j){
      for(int k = j + 1; k < elem.second.size(); ++k){
        col_set.insert({elem.second[j], elem.second[k]});
      }
    }
  }

  for(auto elem: col_set){
    if(collide_2d(rects[elem.first], rects[elem.second])){
      collisions.push_back(elem);
    }
  }
  return collisions;
  
}

vector<Rect> quad_tree(Rect bound){
  vector<Rect> quad_tree_vec;
  Rect bound1;
  bound1.x = bound.x; bound1.y = bound.y; bound1.w = bound.w/2; bound1.h = bound.h/2;
  Rect bound2;
  bound2.x = bound.x + bound.w/2; bound2.y = bound.y; bound2.w = bound.w/2; bound2.h = bound.y/2;
  Rect bound3;
  bound3.x = bound.x; bound3.y = bound.y + bound.h/2; bound3.w = bound.w/2; bound3.h = bound.h/2;
  Rect bound4;
  bound4.x = bound.x + bound.w/2; bound4.y = bound.y + bound.h/2; bound4.w = bound.w/2; bound4.h = bound.h/2;
  quad_tree_vec.push_back(bound1);
  quad_tree_vec.push_back(bound2);
  quad_tree_vec.push_back(bound3);
  quad_tree_vec.push_back(bound4);
  return quad_tree_vec;
}

vector<pair<int, int> > count_collisions_3(vector<Rect> &rects, int depth, Rect bound){
  cout << "enter cc3" << endl;
  vector<pair<int, int> > collisions;
  if(depth == 0 || rects.size() <= 3){
    cout << "enter if 1" << endl;
    //just compute it
    collisions = count_collisions_bf(rects);
  }
  else{
    cout << "enter if 2" << endl;
    //divide and conquer
    vector<Rect> quad_tree_vec = quad_tree(bound);
    
    vector<vector<int> > quad_groups;
    for(int i = 0; i < 4; ++i){
      vector<int> temp_vec;
      quad_groups.push_back(temp_vec);
    }
    cout << "here" << endl;
    for(int i = 0; i < rects.size(); ++i){
      for(int j = 0; j < 4; ++j){
        if(collide_2d(rects[i], quad_tree_vec[j])){
          quad_groups[j].push_back(i);
        }
      }
    }
    cout << "here2" << endl;
    set<pair<int, int> > no_dup;
    vector<pair<int, int> > quad_col_vec;
    for(int i = 0; i < quad_groups.size(); ++i){
      vector<Rect> temp_rects;
      for(int j = 0; j < quad_groups[i].size(); ++j){
        temp_rects.push_back(rects[quad_groups[i][j]]);
      }
      quad_col_vec = count_collisions_3(temp_rects, depth - 1, quad_tree_vec[i]);
      for(int j = 0; j < quad_col_vec.size(); ++j){
        no_dup.insert(quad_col_vec[j]);
      }
    }
    for(auto &elem: no_dup){
      collisions.push_back(elem);
    }
  }
  cout << "here3" << endl;
  return collisions;
  
}

int main(){
  int n; //# of rectangles
  cin >> n;
  vector<Rect> rects(n);
  for (auto &rect : rects) cin >> rect;
  
  auto start_time = high_resolution_clock::now();
  vector<pair<int, int> > bf_col = count_collisions_bf(rects);
  auto stop_time = high_resolution_clock::now();

  auto duration = duration_cast<microseconds>(stop_time - start_time);

  cout << "bf ans: " << bf_col.size() << endl;
    for(int i = 0; i < bf_col.size(); ++i){
        cout << bf_col[i].first << ", " << bf_col[i].second << " ";
    }
    cout << endl;
  cout << "bf time: " << duration.count() << endl;


  start_time = high_resolution_clock::now();
  vector<pair<int, int> > col_vec = count_collisions_2(rects);
  stop_time = high_resolution_clock::now();

  duration = duration_cast<microseconds>(stop_time - start_time);

  cout << "2 ans: " << col_vec.size() << endl;
  cout << "2 time: " << duration.count() << endl; 

  
  Rect bound;
  bound.x = 0; bound.y = 0; bound.w = 100; bound.y = 100;

  start_time = high_resolution_clock::now();
  vector<pair<int, int> > col_vec3 = count_collisions_3(rects, 1, bound);
  stop_time = high_resolution_clock::now();
 
  duration = duration_cast<microseconds>(stop_time - start_time);

  cout << "3 ans: " << col_vec3.size() << endl;
  cout << "3 time: " << duration.count() << endl; 
  

  /*
  {
    // Something like this for each algorithm
    Timer timer;
    auto time = chrono::duration_cast<chrono::millisecon(chrono::high_resolution_clock::now() - start);
    cout << "brute force found " << isects_brute.size() << " in " << timer.elapsed() << endl;
  }
  
  cout << count_collisions_bf(rects).size() << endl;
  */

}





//HOMEWORK
//TURN EACH ALGO INTO CLASS





/*


// pair<int, int> zoneForPoint(int x, int y, int zsize=16) {
pair<int, int> zoneForPoint(pair<int, int> xy, int zsize=16) {
  return {xy.first / zsize, xy.second / zsize};
}



Rect(0, 0, 16, 16);

vector<pair<int, int>> zoneForRect(const Rect &rect, int zsize=16) {
  const pair<int, int> leftbottomz = zoneForPoint({rect.x, rect.y}, zsize);
  const pair<int, int> rightupperz = zoneForPoint({rect.x + rect.w, rect.y + rect.h}, zsize);
  
  vector<pair<int, int>> zones;
  
  for(int i = leftbottomz.first; i <= rightupperz.first; ++i){
    for(int j = leftbottomz.second; j <= rightupperz.second; ++j){
      zones.push_back({i, j});
    }
  }
  return zones;
}

void collide_sh(const vector<Rect> &rects)
{
  unordered_map<pair<int, int>, vector<int>> buckets;
  for(int i = 0; i < rects.size(); ++i){
  	for(const auto &elem: zoneForRect(rects[i], zsize)){
      buckets[elem].push_back(i);
    }
  }
  set<pair<int, int>> intersections;
  for(const auto &elem: buckets){
    const vector<int> &rinds = elem.second;
    for(int i = 0; i < rinds.size(); ++i){
      for(int j = i + 1; j < rinds.size(); ++j){
        if(collide_2d(rinds[i], rinds[j])){
          intersections.insert({min(i, j), max(i, j)});
        }
      }
    }
  }
  
}


class RectangleCollider {
 public:
  void add(const Rect &rect);
  vector<pair<int, int>> intersections();  
  
  // Extra credit
  //return indexes of rectangles that collide with new rect object
  vector<int> intersections(const Rect &rect);
  
 private:
  vector<Rect> rects;
};

  //size of each zone
  int zsize;
  //maps each zone (indexed by x, y) to vector of rects in zone
  unordered_map<pair<int, int>, vector<int>> rects;



   int depth;
   Rect bounds;   // <--- Constructor needs to take bounds
   vector<Rect> rects;
   vector<QuadTree> children;







*/
