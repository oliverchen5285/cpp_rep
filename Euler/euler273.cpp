#include <iostream>
#include <string>
#include <cmath>
#include <math.h>
using namespace std;

int main()
{
  cout << "findme11" << endl;
  long int ans = 0;
  int n[15];
  int ins = 0;
  for(int i = 1; i < 37; i++){
    int a = (4*i)+1;
    bool prime = true;
    for(int j = 2; j < a/2; j++){
      if(a%j == 0){
        prime = false;
      }
    }
    if(prime == true){
      n[ins] = a;
      ins++;
    }
  }
  for(int i = 0; i < 15; i++){
    cout << n[i] << endl;
  }
  bool bin[16];

  for(long i = 1; i < 32768; i++){
    for(int j = 0; j < 16; j++){
      bin[j] = false;
    }
    int okay = i;
    for(int j = 15; j >= 0; j--){
      if(okay - pow(2, j) >= 0){
        bin[j] = true;
        okay = okay - pow(2, j);
      }
    }
    for(int j = 15; j >= 0; j--){
      if(bin[j] == true){
        cout << 1;
      }
      else{
        cout << 0;
      }
    }
    cout << endl;
    long int temp = 1;
    cout << "1";
    for(int j = 0; j < 16; j++){
      if(bin[j] == true){
        temp = temp * n[j];
        cout << " * " << n[j];
      }
    }
    cout << " = " << temp << endl << endl;
    long int sum = 0;
    for(int j = 1; j <= temp; j++){
      int work = sqrt(temp - (j*j));
      if((work*work)+(j*j) == temp){
        cout << work << "^2 + " << j << "^2 = " << temp << endl;
        cout << work*work << " + " << j*j << " = " << temp << endl;
        cout << endl;
        sum = sum + max(work, j);
      }
    }
    ans = ans + sum/2;
  }
  cout << ans << endl;
}

