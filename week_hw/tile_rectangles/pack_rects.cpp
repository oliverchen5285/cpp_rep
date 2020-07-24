#include "base.cpp"
/*
class Tile_dgnl{
private:
  vector<Rect> rect_vec;

  bool des_width(const Rect r1, const Rect r2){
    return r1.width > r2.width;
  }
  bool des_height(const Rect r1, const Rect r2){
    return r1.height > r2.height;
  }
public:
  Tile_dgnl(const vector<Rect> new_rect_vec){
    rect_vec = new_rect_vec;
  }
  
}
*/

bool des_area(const Rect r1, const Rect r2){
  return r1.width * r1.height > r2.width * r2.height;
}

class Tile_bf{ //Instead of bool matrix representing used area, iterate through valid corners to place new rectangle (new rectangle upper left corner always pressed against other corner)
private:
  vector<Rect> rect_vec;

  int width_bound;
  int height_bound;

  //vector<vector<bool>> grid; //I don't know how else to store where rectangles are
  vector<Rect> used_rects = {{0, 0, {0, 0}}}; //initialize with corner first

  int sqr_side;
  /*
  bool des_area(const Rect r1, const Rect r2){
    return r1.width * r1.height > r2.width * r2.height;
  }
  */
  vector<pair<int, int>> pos_corners(const Rect r){
    return {{r.pos.first + r.width, r.pos.second}, {r.pos.first, r.pos.second + r.height}}; //include opposite corner? (first + width, second + height)
  }
public:
  Tile_bf(const vector<Rect> new_rect_vec){
    rect_vec = new_rect_vec;
    
    width_bound = 0;
    height_bound = 0;
    for(const auto &elem: rect_vec){
      width_bound += elem.width;
      height_bound += elem.height;
    }

    cout << "done with initializing width_bound, height_bound" << endl;
    //grid = vector<vector<bool>>(width_bound, vector<bool>(height_bound, false));

    //cout << "done with initializing grid" << endl;
    
    sqr_side = 0;
  }

  pair<int, vector<Rect>> tile_rects(){
    sort(rect_vec.begin(), rect_vec.end(), des_area); //sort rectangles by area

    int new_sqr_side = sqr_side;

    for(auto &elem: rect_vec){ //go through every rectangle
      cout << elem.width << ", " << elem.height << endl;
      int cur_sqr_side = -1;
      pair<int, int> best_pos = {-1, -1};
      //bool break_both = false;
      /*
      for(int i = 0; i < sqr_side + 1; ++i){ //i and j iterate through possible locations to put rectangle
        for(int j = 0; j < sqr_side + 1; ++j){
          bool valid = true;
          for(int k = i; k < i + elem.width; ++k){ //check if possible
            if(grid[k][j]){
              valid = false;
              break;
            } 
          }
          for(int k = j; k < j + elem.height; ++k){
            if(grid[i][k]){
              valid = false;
              break;
            }
          }
          if(valid){
            if(cur_sqr_side == -1 || max(i + elem.width, j + elem.height) < cur_sqr_side){
              cur_sqr_side = max(max(i + elem.width, j + elem.height), sqr_side);
              best_pos = {i, j};
            }
            if(cur_sqr_side == sqr_side){
              cout << "     " << "fits without expanding" << endl;
              break_both = true;
              break;
            }
          }
        }
        if(break_both){
          break;
        }
      }
      */
      for(auto &cur_used_rect: used_rects){ //loop through rectangles again
        for(const auto &corner: pos_corners(cur_used_rect)){ //loop through 2 corners
          bool valid = true;
          for(const auto &other_used_rect: used_rects){ //loop through used rectangles again
            if(collide_2d({elem.width, elem.height, corner}, other_used_rect)){
              valid = false;
              break;
            }
          }
          if(valid){
            //cout << "VALID VALID VALID VALID VALID" << endl;
            int temp_sqr_side = max(corner.first + elem.width, corner.second + elem.height);
            if(cur_sqr_side == -1 || temp_sqr_side < cur_sqr_side){
              //cout << "NEW BEST NEW BEST NEW BEST" << endl;
              cur_sqr_side = temp_sqr_side;
              best_pos = corner;
            }
          }
        }
      }
      elem.pos = best_pos;
      /*
      for(int i = elem.pos.first; i < elem.pos.first + elem.width; ++i){
        for(int j = elem.pos.second; j < elem.pos.second + elem.height; ++j){
          grid[i][j] = true;
        }
      }
      */
      used_rects.push_back(elem);
      sqr_side = max(cur_sqr_side, sqr_side);
      cout << "     " << elem.pos.first << ", " << elem.pos.second << endl;
      cout << "     " << "sqr_side: " << sqr_side << endl;
      /*
      cout << "     " << "grid: " << endl;
      for(int i = 0; i < 400; ++i){
        cout << "     ";
        for(int j = 0; j < 400; ++j){
          cout << grid[i][j] << " ";
        }
        cout << endl;
      }
      cout << endl;
      */
    }
    return {sqr_side, rect_vec};
  }
  
};
/*
class Tile_grav{

};
*/
int main(){
  ifstream fin("rect_cases.txt"); //to be honest I should have just made classes to check stuff in the same file -- actually I'll just do that
  ofstream fout("rect_w_pos.txt");

  int cases;
  fin >> cases;
  
  vector<Rect> rect_vec;
  
  for(int i = 0; i < cases; ++i){
    int width, height;
    fin >> width >> height;
 
    Rect temp_rect(width, height);
    rect_vec.push_back(temp_rect);
  }
  cout << "done with input" << endl;
  for(const auto &elem: rect_vec){
    cout << elem.width << ", " << elem.height << endl;
  }
  cout << endl;
  Tile_bf tile_bf(rect_vec);
  pair<int, vector<Rect>> ans = tile_bf.tile_rects();
  fout << ans.first << " " << cases << endl;
  for(const auto &elem: ans.second){
    fout << elem.width << " " << elem.height << " " << elem.pos.first << " " << elem.pos.second << endl;
  }
}
