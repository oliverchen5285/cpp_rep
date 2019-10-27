#include <iostream>
#include <string>
#include <vector>
using namespace std;

//find number of distinct strings you can write using only N pairs of balanced parenthesis


vector<string> repeat;

void func(int n, string ans){
  if(n == 0){
    bool seen = false;
    string temp = "()";
    for(int i = 0; i < repeat.size(); i++){
        if(temp == repeat[i]){
          seen = true;
        }
      }
      if(seen == false){
        repeat.push_back(temp);
      }

    return;
  }
  n = n-2;
  for(int i = 0; i < ans.length(); i++){
    if(ans[i] == '('){
      string temp = ans.substr(0, i);
      string temp2 = ans.substr(i, ans.length()-i);
      string temp3 = "()";
      temp.append(temp3);
      temp.append(temp2);
      cout << temp << endl;
      bool seen = false;
      for(int i = 0; i < repeat.size(); i++){
        if(temp == repeat[i]){
          seen = true;
        }
      }
      if(seen == false){
        repeat.push_back(temp);
      }
      func(n, temp);
      
    }
    if(ans[i] == ')'){
      string temp = ans.substr(0, i+1);
      string temp2 = ans.substr(i+1, ans.length()-i-1);
      string temp3 = "()";
      temp.append(temp3);
      temp.append(temp2);
      cout << temp << endl;
      bool seen = false;
      for(int i = 0; i < repeat.size(); i++){
        if(temp == repeat[i]){
          seen = true;
        }
      }
      if(seen == false){
        repeat.push_back(temp);
      }
      func(n, temp);
    }
    if(i != ans.length()-1 && ans[i] == '(' && ans[i+1] == ')'){
      string temp = ans.substr(0, i+1);
      string temp2 = ans.substr(i+1, ans.length()-i-1);
      string temp3 = "()";
      temp.append(temp3);
      temp.append(temp2);
      cout << temp << endl;
      bool seen = false;
      for(int i = 0; i < repeat.size(); i++){
        if(temp == repeat[i]){
          seen = true;
        }
      }
      if(seen == false){
        repeat.push_back(temp);
      }
      func(n, temp);
    }

  }
  
}

int main()
{
  int n;
  cin >> n;
  string ans = "()";
  func(2*n-2, ans);
  cout << endl;
  int finans = 0;
  for(int i = 0; i < repeat.size(); i++){
    if(repeat[i].size() == 2*n){
      cout << repeat[i] << endl;
      finans++;
    }
  }
  cout << finans << endl;
}

