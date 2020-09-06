#include <iostream>
#include <vector>
#include <map>
using namespace std;

long tiles(int length, const vector<int> &blocks, map<int, long> &memo){
  if(length < 0){
    return 0;
  }
  if(length < 2){
    return 1;
  }
  if(memo.find(length) != memo.end()){
    return memo[length];
  }
  long ans = 0;
  ans += tiles(length - 1, blocks, memo);
  for(const auto &elem: blocks){
    ans += tiles(length - elem, blocks, memo);
  }
  memo[length] = ans;
  return ans;
}

long tiles_dp(int length, const vector<int> &blocks){
  vector<long> dp_vec(length + 1, 1); //starts at 0, ends at length

  for(int i = 2; i <= length; ++i){
    dp_vec[i] = 0;
    dp_vec[i] += dp_vec[i-1];
    for(const auto &elem: blocks){
      dp_vec[i] += (i-elem >= 0)? dp_vec[i-elem]: 0;
    }
  }
  return dp_vec.back();

}
int main() {
  long ans = 0;
  vector<int> blocks = {2, 3, 4};
  map<int, long> memo;
  ans += tiles_dp(50, blocks);
  cout << ans << endl;
}
