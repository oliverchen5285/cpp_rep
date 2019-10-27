#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int b[8] = {200, 100, 50, 20, 10, 5, 2, 1};
int sum = 0;

int coins(int a, int x){
  if(a == 0){
    return 1;
  }
  for(int i = x; i < 8; i++){
    if(a - b[i] >= 0){
      x = i;
      for(int j = 0; j <= floor(a/b[i]); j++){
        cout << "i " << i << endl;
        cout << "a " << a << endl;
        cout << "j * b[i] " << j << " * " << b[i] << " = " << j*b[i] << endl;
        cout << "a - j*(b[i]) " << a - j*(b[i]) << endl;
        if(x == 7){
          sum = sum + coins(a - j*(b[i]), x+);
        }
        else{
          sum = sum + coins(a - j*(b[i]), x+1);
        }
      }
    }
  }
  return sum;
}

int main()
{
  cout << "donkey3" << endl;
  cout << coins(200, 0) << endl;
}

