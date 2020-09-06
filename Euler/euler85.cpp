#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdlib>
using namespace std;

unsigned long long int choose2(int x){
  return (x * (x-1))/2;
}

unsigned long long int rects(const pair<int, int> cur_rect){
  return choose2(cur_rect.first + 1) * choose2(cur_rect.second + 1);
}

bool sort_rect(const pair<int, int> x, const pair<int, int> y){
  return x.second < y.second;
}

vector<pair<int, int>> gen_rects(int upper_bound){
  vector<pair<int, int>> rects_vec;
  for(int i = 1; i < upper_bound; ++i){
    for(int j = 1; j <= i; ++j){
      rects_vec.push_back({i*j, rects({i, j})});
    }
  }
  sort(rects_vec.begin(), rects_vec.end(), sort_rect);
  return rects_vec;
}

unsigned long long int dist(unsigned long long int x, unsigned long long int y){
  if(x > y){
    return x - y;
  }
  return y - x;
}

int count_rects(){
  vector<pair<int, int>> rects_vec = gen_rects(200);
  int area = 0;
  int best_rects = 0;
  for(const auto &elem: rects_vec){
    if(abs(2000000 - elem.second) < abs(2000000 - best_rects)){
      best_rects = elem.second;
      area = elem.first;
    }
  }
  return area;
}



int main(){
  //cout << rects({1, 1}) << endl;
  cout << "ans: " << count_rects() << endl;
}
