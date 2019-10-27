#include <iostream>
#include <string>
using namespace std;

//find min number of swaps to sort array of n distinct numbers


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

2 3 4 5 1

1 3 4 5 2
1 2 4 5 3
1 2 3 5 4
1 2 3 4 5



5 4 3 2 1

1 4 3 2 5
1 2 3 4 5

4 3 5 1 2

1 3 5 4 2
1 2 5 4 3
1 2 3 4 5