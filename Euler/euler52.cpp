//this was surprisingly fast
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int permuted_multiples(){
  int cur = 1;
  while(true){
    bool valid = true;
    for(int i = 2; i <= 6; ++i){
      string str_mult = to_string(cur * i);
      string str_cur = to_string(cur);
      sort(str_mult.begin(), str_mult.end());
      sort(str_cur.begin(), str_cur.end());
      if(str_mult != str_cur){
        valid = false;
        break;
      }
    }
    if(valid){
      break;
    }
    ++cur;
  }
  return cur;
}

int main(){
  cout << permuted_multiples() << endl;
}
