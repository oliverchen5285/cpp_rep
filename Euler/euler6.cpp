#include <iostream>
#include <string>
using namespace std;

int main()
{
  int a = 5050*5050;
  long b = 0;
  for(int i = 1; i <= 100; i++){
    b = b + (i*i);
    cout << b << endl;
  }
  cout << a - b;
}

