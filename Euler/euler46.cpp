#include <iostream>
#include <string>
#include <math.h>
using namespace std;

int main()
{
  cout << "findme3" << endl;
  int temp;
  bool gold;
  int a[1000000];
  int counter = 0;
  bool prime;
  cout << "generating primes..." << endl;
  for(int i = 3; i < 40401; i++){
    prime = true;
    for(int j = 2; j <= i/2; j++){
      if(i%j == 0){
        prime = false;
      }
    }
    if(prime == true){ 
      a[counter] = i;
      //cout << i << endl;
      counter++;
    }
  }
  cout << "done" << endl;
  int pritest = 3;
  int keeper = 0;
  int other;
  cout << "testing..." << endl;
  for(int i = 1; i <= 100; i++){
    for(int j = i; j <= 100; j++){
      temp = (2*i + 1)*(2*j + 1);
      cout << temp << endl;
      gold = false;
      keeper = 0;
      pritest = 3;
      while(pritest < temp){
        cout << " " << pritest << endl;
        other = sqrt((temp - pritest)/2);
        if(2*other*other + pritest == temp){
          gold = true;
        }
        keeper++;
        pritest = a[keeper];
      if(gold == true){
        cout << a[keeper-1] << " + " << other << "^2 = " << temp << endl;
      }
      }
      if(gold == false){
        cout << "found answer! " << temp << endl;
      }
    }
  }
}

