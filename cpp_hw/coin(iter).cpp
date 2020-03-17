#include <iostream>
#include <string>
#include <vector>
using namespace std;



int main()
{
  vector<int> coins;
  int total;
  cin >> total;
  int n;
  cin >> n;
  int temp;
  for(int i = 0; i < n; i++){
    cin >> temp;
    coins.push_back(temp);
  }
  int ans[total][n];
  for(int i = 0; i < total; i++){
    for(int j = 0; j < n; j++){
      ans[i][j] = -1;
      if(i == 0){
        ans[i][j] = 1;
      }
      else if(j == 0){
        ans[i][j] = 0;
      }
    }
  }
  //cout << "reached" << endl;
  int firstleft;
  int secondleft;

  int firstright;
  int secondright;
  for(int i = 1; i < total; i++){
    for(int j = 1; j < n; j++){
      //cout << i << "," << j << " -- ";
      firstleft = 0;
      secondleft = j;
      if(i - coins[j] >= 0){
        firstleft = i - coins[j];
      }
      
      firstright = i;
      secondright = j-1;
      
      ans[i][j] = ans[firstleft][secondleft] + ans[firstright][secondright];
      //cout << ans[i][j] << endl;
    }
  }

  for(int i = 0; i < total; i++){
    for(int j = 0; j < n; j++){
      cout << ans[i][j] << " ";
    }
    cout << endl;
  }

  cout << ans[total-1][n-1] << endl;
}

