#include <iostream>
#include <string>
#include <vector>
using namespace std;

int f(int total, vector <int> coins){
  if(total == 0){
    return 1;
  }
  if(total < 0){
    return 0;
  }
  if(coins.empty()){
    return 0;
  }
  vector <int> temp = coins;
  temp.pop_back();
  return f(total, temp) + f(total-coins.back(), coins);
  
}

int main()
{
  vector <int> coins;
  int total;
  cin >> total;
  int n;
  cin >> n;
  int temp;
  for(int i = 0; i < n; i++){
    cin >> temp;
    coins.push_back(temp);
  }
  cout << f(total, coins);
}

