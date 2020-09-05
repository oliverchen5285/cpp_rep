#include <iostream>
#include <vector>
using namespace std;

long combs_dp(const int length, const int block){
  vector<long> dp_vec(length + 1, 1); //starting at 0, ending at length
  int red_sum = 0;
  int sum_index = -1; //super simple optimization that I was too lazy to implement in 114 (I guess it works now yay)

  for(int i = block; i <= length; ++i){
    dp_vec[i] = 0; //reset
    dp_vec[i] += dp_vec[i-1]; //pick black block
    red_sum += (sum_index >= 0)? dp_vec[sum_index]: 0;
    ++sum_index;
    dp_vec[i] += red_sum;
    dp_vec[i] += 1; //all filled out (technically I can just not reset it but yea)
  }
  return dp_vec.back();
}

int main(){
  int i = 51;
  while(true){
    if(combs_dp(i, 50) > 1000000){
      cout << i << endl;
      return 0;
    }
    ++i;
  }
}
