#include <iostream>
#include <vector>
using namespace std;

int ways(const int &n, const vector<int> &coins, int sum, int index){
  cout << sum << endl;
  if(sum == n){
    return 1;
  }
  if(sum > n){
    return 0;
  }
  int ans = 0;
  for(int i = index; i < coins.size(); ++i){
    ans += ways(n, coins, sum + coins[i], i);
  }
  return ans;
}

int main(){
  cout << ways(200, {1, 2, 5, 10, 20, 50, 100, 200}, 0, 0) << endl;
}
