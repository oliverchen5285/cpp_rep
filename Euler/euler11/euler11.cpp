#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

int main(){
  ifstream fin("nums.txt");
  
  vector<vector<int>> nums;
  for(int i = 0; i < 20; ++i){
    vector<int> temp_vec;
    for(int j = 0; j < 20; ++j){
      int temp_int;
      fin >> temp_int;
      temp_vec.push_back(temp_int);
    }
    nums.push_back(temp_vec);
  }
  
  int ans = 1;
  for(int i = 0; i < 20; ++i){
    for(int j = 0; j < 20; ++j){
      if(i >= 3 && j <= 16){
        ans = max(ans, nums[i][j] * nums[i-1][j+1] * nums[i-2][j+2] * nums[i-3][j+3]);
      }
      if(j <= 16){
        ans = max(ans, nums[i][j] * nums[i][j+1] * nums[i][j+2] * nums[i][j+3]);
      }
      if(i <= 16 && j <= 16){
        ans = max(ans, nums[i][j] * nums[i+1][j+1] * nums[i+2][j+2] * nums[i+3][j+3]);
      }
      if(i <= 16){
        ans = max(ans, nums[i][j] * nums[i+1][j] * nums[i+2][j] * nums[i+3][j]);
      }
    }
  }
  cout << ans << endl;
}
