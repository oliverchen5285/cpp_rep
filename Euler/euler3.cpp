#include <iostream>
#include <string>
using namespace std;

void add_factors(long n){
    long temp_n = n;
    int i = 2;
    while(true){
        while(n % i == 0){
            cout << i << endl;
            n /= i;
        }
        if(i == 2){
            i += 1;
        }
        else{
            i += 2;
        }
        
        if(i == temp_n/2){
            break;
        }
    }
    return;
}

int main(){
  long n = 600851475143;
  add_factors(n);
  
  
}

