#include <iostream>
#include <string>
using namespace std;

int main()
{
  int counter = 1;
  int a = 3;
  while(counter < 10002){
    bool prime = true;
    for(int i = 2; i < a/2; i++){
      if(a%i == 0){
        prime = false;
      }
    }
    if(prime == true){
      counter++;
      cout << a << endl;
    }
    a++;
  }
  cout << a-1 << endl;
}

