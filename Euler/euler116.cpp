#include <iostream>
#include <vector>
#include <map>
using namespace std;

long tiles(int length, const int block, map<int, long> &memo){
  if(length < block){
    return 1;
  }
  if(memo.find(length) != memo.end()){
    return memo[length];
  }
  long ans = 0;
  ans += tiles(length - 1, block, memo);
  ans += tiles(length - block, block, memo);
  memo[length] = ans;
  return ans;
}

long tiles_dp(int length, const int block){
  vector<long> dp_vec(length + 1, 1); //starts at 0, ends at length

  for(int i = block; i <= length; ++i){
    dp_vec[i] = 0;
    dp_vec[i] += dp_vec[i-1];
    dp_vec[i] += dp_vec[i-block];
  }
  return dp_vec.back();

}
int main() {
  long ans = 0;
  //map<int, long> memo;
  ans += tiles_dp(50, 2) - 1;
  ans += tiles_dp(50, 3) - 1;
  ans += tiles_dp(50, 4) - 1;
  cout << ans << endl;
}
