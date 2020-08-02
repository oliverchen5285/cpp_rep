#include <iostream>
#include <algorithm>
using namespace std;

long long fact_to(int n, int r){ 
  cout << "enter fact, n = " << n << endl;
  long long ans = 1;
  for(int i = n; i > r; --i){
    ans *= i;
  }
  cout << "exit fact, ans = " << ans << endl;
  return ans;
}

long long choose(int n, int r){
  cout << "enter choose, (n, r) = " << n << ", " << r << endl;
  long long ans = fact_to(n, max(r, n-1)) / (fact_to(min(r, n-1), 1));
  cout << "exit choose, ans = " << ans << endl;
  return ans;
}

int comb_selections(){
  int ans = 0;
  for(int i = 1; i <= 100; ++i){
    for(int j = 1; j <= i/2; ++j){
      cout << "(i, j) = " << i << ", " << j << endl;
      if(choose(i, j) > 1000000){
        ++ans;
      }
    }
  }
  return ans;
}
 
int main(){
  cout << comb_selections() << endl;
  return 0;
}
