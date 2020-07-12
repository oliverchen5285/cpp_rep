#include "base.cpp"

string valid(const vector<Rect> &rect_vec, const int sqr_side){
  //if rectangles not in square
  for(const auto &elem: rect_vec){
    if(elem.width + elem.pos.first > sqr_side || elem.height + elem.pos.second > sqr_side){
      cout << elem.width << ", " << elem.height << " - " << elem.pos.first << ", " << elem.pos.second << endl;
      return "rectangles not in square";
    }
  }
  //I would use my rectangle collision files, but I didn't want to redefine Rect and everything (and ya know I'll prob be testing with small sample sizes) sooo brute force
  for(int i = 0; i < rect_vec.size(); ++i){
    for(int j = i + 1; j < rect_vec.size(); ++j){
      if(collide_2d(rect_vec[i], rect_vec[j])){
        return "rectangles collide";
      }
    }
  }
  return "ok";
}

pair<double, int> area_wasted_pct(const vector<Rect> &rect_vec, const int sqr_side){
  int total_area = sqr_side * sqr_side;
  
  for(const auto &elem: rect_vec){
    total_area -= elem.width * elem.height;
  }
  
  return {(float(sqr_side * sqr_side) / (float)total_area), total_area}; //you want both these numbers to be small
}

int main(){
  ifstream fin("rect_w_pos.txt");
  //I'll just output to stdout

  int sqr_side, cases; //enclosing square location assumed to be {0, 0}
  fin >> sqr_side >> cases;

  cout << sqr_side << " " << cases << endl;

  vector<Rect> rect_vec;

  for(int i = 0; i < cases; ++i){
    int width, height;
    pair<int, int> pos;
    fin >> width >> height >> pos.first >> pos.second;

    Rect temp_rect(width, height, pos);
    rect_vec.push_back(temp_rect);    
  }

  for(const auto &elem: rect_vec){
    cout << elem.width << ", " << elem.height << " - " << elem.pos.first << ", " << elem.pos.second << endl;
  }
  cout << endl;

  //first check if input is valid (if rectangles collide, if rectangles not in square)
  const string state = valid(rect_vec, sqr_side);
  if(state != "ok"){
    cout << state << endl;
    return 0;
  }

  const pair<double, int> area_wasted_pair = area_wasted_pct(rect_vec, sqr_side);
  cout << area_wasted_pair.first << ", " << area_wasted_pair.second << endl;
  return 0;
  
  
}
