#include <iostream>
#include <string>
using namespace std;

int main()
{
  bool find = false;
  int n = 7500;
  int temp;
  int fac;
  cout << "yay3" << endl;
  while(find == false){
    temp = (n*(n+1))/2;
    cout << temp << " " << n << endl;
    
    fac = 0;
    cout << " ";
    //optimize this factoring segment by finding factors of "n" and "n+1" separately
    for(int i = 1; i <= temp; i++){
      if(temp%i == 0){
        fac++;
        cout << i << " ";
      }
    }
    cout << endl << " " << fac << endl;
    if(fac >= 500){
      find = true;
    }
    n++;
  }
  cout << temp << endl;
}

