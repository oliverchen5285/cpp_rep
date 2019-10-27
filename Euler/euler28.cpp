#include <iostream>
#include <string>
using namespace std;

int main()
{
  long a = 1;
  long ans = 1;
  for(int i = 0; i < 500; i++){
    for(int j = 0; j < 4; j++){
      cout << a << endl;
      a = a + 2*(i+1);
      ans = ans + a;
    }
  }
  cout << ans << endl;
}

