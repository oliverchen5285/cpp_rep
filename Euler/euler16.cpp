#include <iostream>
#include <string>
using namespace std;

string strMult(string n){
  n.insert(0, "0");
  string ans = "";
  int carry = 0;
  for(int i = n.length() - 1; i >= 0; --i){
    int temp_dig = n[i] - '0';
    int new_dig = temp_dig * 2 + carry;
    carry = new_dig/10;
    new_dig = new_dig % 10;
    ans.insert(0, to_string(new_dig));
  }
  if(ans[0] == '0'){
    ans.erase(0, 1);
  }
  return ans;
}

string strPow(int n){
  string ans = "1";
  for(int i = 0; i < n; ++i){
    cout << ans << endl;
    ans = strMult(ans);
  }
  return ans;
}

int digSum(const string &n){
  int sum = 0;
  for(const auto &elem: n){
    int temp_dig = elem - '0';
    sum += temp_dig;
  }
  return sum;
}

int main(){
  int n = 1000;
  string num = strPow(n);
  cout << num << ", " << digSum(num) << endl;
}

