#include <iostream>
#include <string>
using namespace std;

int main(){
  int ans = 0;
  for(int i = 110; i < 1000; i = i + 11){
    for(int j = 100; j < 1000; j++){
      int n = i*j;
      if(n % 1000000 == n % 100000){
        continue;
      }
      //cout << n << " ";
      bool pal = true;
      if(n % 10 != (n - n % 100000)/100000){
        pal = false;
      }
      else{
        cout << n << " passed 1!" << endl;
      }
      if(((n%100) - (n%10))/10 != ((n%100000) - (n%10000))/10000){
        pal = false;
      }
      else{
        cout << n << " passed 2!" << endl;
      }
      if((n%10000-n%100)%11 != 0){
        pal = false;
      }
      else{
        cout << n << " passed 3!" << endl;
      }
      if(pal == true && n > ans){
        ans = n;
      }
    }
  }
  cout << ans << endl;
}

