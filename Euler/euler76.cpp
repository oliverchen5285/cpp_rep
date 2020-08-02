#include <iostream>
using namespace std;

int ways(int total, int max, int count){
  if(total == 0 && count >= 2){
    return 1;
  }
  if(total < 0){
    return 0;
  }
  int ans = 0;
  for(int i = 1; i <= max; ++i){
    ans += ways(total - i, i, count + 1);
  }
  return ans;
}

int main(){
  cout << ways(100, 100, 0) << endl;
}
