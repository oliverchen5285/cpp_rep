#include <iostream>
#include <math.h>
#include <unistd.h>
using namespace std;

int main(){
  bool a = fork();
  bool b = fork();

  double x = 1.0;
  for(int i = 0; i < 100000000; ++i){
    x = cos(x + i);
  }

  cout << a << b << endl;
  return 0;
}
