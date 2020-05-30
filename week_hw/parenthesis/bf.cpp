#include "bf.h"

vector<string> genAll(const int &n){
  vector<string> ans;
  int posnum = (int)(pow(2, 2*n) + 0.5);
  for(int i = 0; i < posnum; ++i){
    string temp_str = "";
    for(int j = 0; j < n * 2; ++j){
      if(i & (1 << j)){
        temp_str += "(";
      }
      else{
        temp_str += ")";
      }
    }
    ans.push_back(temp_str);
  }
  return ans;
}

bool valid(string x){
  int count = 0;
  for(const auto &elem: x){
    if(elem == '('){
      ++count;
    }
    else{
      --count;
    }
    if(count < 0){
      return false;
    }
  }
  return count == 0;
}

vector<string> bf_paren(const int &n){
  vector<string> allpos = genAll(n);
  vector<string> ans;
  for(const auto &elem: allpos){
    if(valid(elem)){
      ans.push_back(elem);
    }
  }
  return ans;
}
