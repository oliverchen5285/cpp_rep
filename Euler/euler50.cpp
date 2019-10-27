#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
  bool prime;
  vector<int> a;
  for(int i = 3; i < 1000000; i++){
    prime = true;
    for(int j = 2; j <= i/2; j++){
      if(i%j == 0){
        prime = false;
      }
    }
    if(prime == true){
      a.push_back(i);
    }
  }
  int temp;
  int ans = 0;
  for(int i = 0; i < a.size()-1; i++){
    for(int j = i; j < a.size()-1; j++){
      temp = 0;
      for(int k = i; k <= j; k++){
        temp = temp + a[k];
      }
      prime = true;
      for(int k = 2; k <= temp/2; k++){
        if(temp%k == 0){
          prime = false;
        }
      }
      if(prime == true){
        if(j-i+1 > ans){
          ans = j-i+1;
        }
      }
    }
  }
  cout << ans << endl;
}

