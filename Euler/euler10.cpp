#include <iostream>
#include <string>
using namespace std;

int main()
{
  long ans = 2;
  int i = 3;
  while(i < 2000000){
    bool prime = true;
    for(int j = 2; j <= i/2; j++){
      if(i%j == 0){
        prime = false;
      }
    }
    if(prime == true){
      cout << i << endl;
      ans = ans + i;
    }
    i++;
  }
  cout << ans << endl;
}

