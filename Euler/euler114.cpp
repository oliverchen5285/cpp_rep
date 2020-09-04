#include <iostream>
#include <vector>
#include <utility>
#include <map>
using namespace std;

map<pair<int, bool>, long> memo;

long combs(int depth, bool prev_red){
  if(depth < 3){
    return 1;
  }
  if(memo.find({depth, prev_red}) != memo.end()){
    return memo[{depth, prev_red}];
  }
  long ans = 0;
  //black square
  ans += combs(depth-1, false);

  //red square (repeat because it can be a part of previous chunks?)
  //can be part of chunks later
  if(!prev_red){
    for(int i = 3; i <= depth; ++i){ //possible chunk sizes
      ans += combs(depth - i, true);
    }
  }
  memo[{depth, prev_red}] = ans;
  return ans;
}

long combs_dp(int length){
  vector<long> dp_vec(length + 1, 1); //starting at 0, ending at length

  for(int i = 3; i <= length; ++i){
    dp_vec[i] = 0; //reset
    dp_vec[i] += dp_vec[i-1]; //pick black block
    for(int j = i-4; j >= 0; --j){ //pick red blocks -- start at -4 (not -3) because you skip 1 black block
      dp_vec[i] += dp_vec[j];
    }
    dp_vec[i] += 1; //all filled out (technically I can just not reset it but yea)
  }
  return dp_vec.back();
}

int main(){
  for(int i = 0; i <= 50; ++i){
    cout << i << ": " << combs(i, false) << ", " << combs_dp(i) << endl;
  }
}
