#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <utility>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <algorithm>
using namespace std;

struct Rect{
  int x, y, x2, y2;
};

vector<Rect> gen_Bounds(int minx, int miny, int maxx, int maxy, int num){
  srand(time(0));

  vector<Rect> bounds;
  for(int i = 0; i < num; ++i){
    Rect temp_rect;
    temp_rect.x = 0;
    temp_rect.y = 0;

    temp_rect.x2 = rand() % maxx;
    temp_rect.y2 = rand() % maxy;
    
    bounds.push_back(temp_rect);
  }
  return bounds;
}

vector<Rect> gen_Rect_forBound(Rect bound, int num){
  srand(time(0));

  vector<Rect> rects;
  for(int i = 0; i < num; ++i){
    Rect temp_rect;
    temp_rect.x = rand() % (bound.x2 - 1);
    temp_rect.y = rand() % (bound.y2 - 1);

    temp_rect.x2 = temp_rect.x + (rand() % (min(bound.x2 - temp_rect.x, 100))) + 1;
    temp_rect.y2 = temp_rect.y + (rand() % (min(bound.y2 - temp_rect.y, 100))) + 1;

    rects.push_back(temp_rect);
  }
  return rects;
}

int main(){

  ofstream fout("rect_cases.txt");  

  int case_num = 10;

  vector<Rect> bounds = gen_Bounds(0, 0, 1000, 1000, case_num);
  
  fout << case_num << endl;

  fout << endl << endl;

  for(const auto elem: bounds){
    int rect_num = 40 + (rand() % 40);
    vector<Rect> rects = gen_Rect_forBound(elem, rect_num);
    fout << elem.x << " " << elem.y << " " << elem.x2 << " " << elem.y2 << endl;
    fout << rect_num << endl;
    for(const auto elem2: rects){
      fout << elem2.x << " " << elem.y << " " << elem.x2 << " " << elem.y2 << endl;
    }
    fout << endl;
  }
}
