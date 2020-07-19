#include <iostream>
#include <algorithm>
using namespace std;


int main(){
  string num = "0123456789";
  for(int i = 1; i < 1000000; ++i){
    next_permutation(num.begin(), num.end());
  }    
  cout << num << endl;
}
