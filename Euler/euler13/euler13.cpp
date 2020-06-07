#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

void sameDigits(string &a, string &b){
  //a has more digits than b
  a.insert(0, "0");
  int b_len = b.length();
  for(int i = 0; i < a.length() - b_len; ++i){
    b.insert(0, "0");
  }
}

string strAdd(string a, string b){
  //a has more digits than b
  string ans = "";
  sameDigits(a, b);
  //same digits
  int carry = 0;
  for(int i = a.length()-1; i >= 0; --i){
    int temp_a = a[i] - '0';
    int temp_b = b[i] - '0';
    int temp_dgt = temp_a + temp_b + carry;
    if(temp_dgt >= 10){
      temp_dgt = temp_dgt % 10;
      carry = 1;
    }
    else{
      carry = 0;
    }
    ans.insert(0, to_string(temp_dgt));
  }
  if(ans[0] == '0'){
    ans.erase(0, 1);
  }
  return ans;
}

string allSum(vector<string> nums){
  string sum = nums[0];
  
  for(int i = 1; i < 100; ++i){
    cout << sum << endl;
    sum = strAdd(sum, nums[i]);
    //cout << sum << endl;
  }
  
  return sum;
}

int main(){
  ifstream fin("nums.txt");
  
  vector<string> nums(100);
  
  for(auto &elem: nums){
    fin >> elem;
  }
  
  string sum = allSum(nums);
  
  cout << sum.substr(0, 10) << endl;
  
  
}
