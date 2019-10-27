#include <iostream>
#include <string>
#include <vector>
using namespace std;


int main(){
  long a = 600851475143;
  //cout << a << endl;
  long i = 3;
  long j;
  bool pri;
  vector <int> primes;
  primes.push_back (2);
  while(i < a/2){
    pri = true;
    j = 2;
    while(j <= i/2){
      if(i%j == 0){
        pri = false;
      }
      j++;
    }
    if(pri == true){
      primes.push_back (i);
    }
    i++;
  }
  long ans = 0;
  while(a != 1){
    for(int i = 0; i < primes.size(); i++){
      if(a % primes[i] == 0){
        a = a / primes[i];
        if(primes[i] > ans){
          ans = primes[i];
        }
        i = 0;
      }
    }
  }
  cout << ans << endl;
}

