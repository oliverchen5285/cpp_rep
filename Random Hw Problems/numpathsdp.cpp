#include <iostream>
#include <string>
using namespace std;

int main()
{
  int a, b;
  cin >> a >> b;
  int paths[a][b];
  for(int i = 0; i < a; i++){
    for(int j = 0; j < b; j++){
      paths[i][j] = 0;
    }
  }
  int first;
  int second;
  for(int i = 0; i < a; i++){
    for(int j = 0; j < b; j++){
      if(i == 0 && j == 0){
          first = 0;
          second = 1;
      }
      else if(i == 0 && j!= 0){
        first = 0;
        second = paths[i][j-1];
      }
      
      else if(j == 0 && i!= 0){
        second = 0;
        first = paths[i-1][j];
      }
      else{
        first = paths[i-1][j];
        second = paths[i][j-1];
      }
      paths[i][j] = first + second;
    }
  }
  for(int i = 0; i < a; i++){
      for(int j = 0; j < b; j++){
          cout << paths[i][j] << " ";
      }
      cout << endl;
  }
  cout << paths[a-1][b-1] << endl;
}


