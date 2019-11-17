#include <iostream>
#include <string>
using namespace std;

//recursive with memoization
int memo[100][100];

int recurs(int a, int b){
    if(memo[a][b] != -1){
        cout << "found " << a << "," << b << " " << memo[a][b] << endl;
        return memo[a][b];
    }
    int first;
    int second;
    if(a == 0 && b == 0){
        return 1;
    }
    else if(a == 0 && b!= 0){
        first = 0;
        second = recurs(a, b-1);
        cout << a << "," << b-1 << " " << second << endl;
        memo[a][b-1] = second;
    }
    else if(a != 0 && b== 0){
        second = 0;
        first = recurs(a-1, b);
        cout << a-1 << "," << b << " " << first << endl;
        memo[a-1][b] = first;
    }
    else{
        first = recurs(a-1, b);
        second = recurs(a, b-1);
        cout << a << "," << b-1 << " " << second << endl;
        cout << a-1 << "," << b << " " << first << endl;
        memo[a-1][b] = first;
        memo[a][b-1] = second;
    }
    return first + second;
}

int main()
{
  
  
  int a, b;
  cin >> a >> b;
  for(int i = 0; i < a; i++){
      for(int j = 0; j < b; j++){
          memo[i][j] = -1;
      }
  }
  memo[0][0] = 1;
  for(int i = 0; i < a; i++){
      for(int j = 0; j < b; j++){
          cout << memo[i][j] << " ";
      }
      cout << endl;
  }
  cout << endl;
  cout << recurs(a-1, b-1) << endl;
  for(int i = 0; i < a; i++){
      for(int j = 0; j < b; j++){
          cout << memo[i][j] << " ";
      }
      cout << endl;
  }
}