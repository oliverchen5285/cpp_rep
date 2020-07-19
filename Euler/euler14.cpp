// compile with -Wall -Wpedantic -Werror
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
using namespace std;

unordered_map<int, int> memo;

int seq(long cur, int depth){
  cout << cur << " ";
  if(cur == 1){
    return depth;
  }

  
  int ans;
  if(cur % 2 == 0){
    if(memo.find(cur / 2) == memo.end()){
      memo[cur/2] = seq(cur/2, 1);
    }
    depth += memo[cur/2];
  }
  else{
    if(memo.find(3*cur + 1) == memo.end()){
      memo[3*cur + 1] = seq(3*cur + 1, 1);
    }
    depth += memo[3*cur + 1];
  }
  return depth;
}

int collatz(){
  pair<int, int> ans = {1, 0};
  for(int i = 1; i <= 1000000; ++i){
    int temp_ans = seq(i, 1);
    cout << " - ";
    cout << i << ", " << temp_ans << endl;
    if(temp_ans > ans.second){
      ans.first = i;
      ans.second = temp_ans;
    }
  }
  return ans.first;
}

int main(){
  //cout << seq(13, 1) << endl;
  
  cout << collatz() << endl;
}
