#include <iostream>
#include <string>
using namespace std;

int main()
{
  int n;
  cin >> n;
  int a[n];
  for(int i = 0; i < n; i++){
    cin >> a[i];
  }
  int ans = n;
  for(int i = 0; i < n; i++){
    if(a[i] == i+1){
      ans--;
    }
  }
  for(int i = 0; i < n; i++){
    for(int j = i+1; j < n; j++){
      if(i+1 == a[j] && j+1 == a[i]){
        ans--;
      }
    }
  }
  cout << ans << endl;
}

5 4 3 2 1

3 5 4 1 2

3 2 4 1 5
4 2 3 1 5
1 2 3 4 5

