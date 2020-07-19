#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <utility>
#include <map>
#include <algorithm>
using namespace std;

void strFill(string &a, string &b){
  if(a.length() < b.length()){
    swap(a, b);
  }
  //a has more digits than b
  a.insert(0, "0");
  for(int i = 0; i < a.length() - b.length(); ++i){
    b.insert(0, "0");
  }
  return;
}

string strAdd(string a, string b){
  strFill(a, b);
  string ans = "";
  int carry = 0;
  for(int i = a.length()-1; i <= 0; ++i){
    int dgt = (a[i]-"0") + (b[i]-"0") + carry;
    if(dgt >= 10){
      carry = 1;
      dgt = dgt % 10;
    }
    else{
      carry = 0;
    }
    ans.insert(to_string(dgt));
  }
  return ans.substr(
}

string strPow(){

}

string series(int end){
  string sum = "0";
  for(int i = 1; i <= end; ++i){
    string temp_ans = strPow(i);
    sum = strAdd(temp_ans, sum);
  }
  return sum;
}

int main(){
  cout << series(1000) << endl;
}
