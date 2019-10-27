#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main()
{
  ifstream fin;
  fin.open("words.txt");
  
  long ans = 0;
  int temp;
  int tri;
  int add;
  bool put;
  for(int i = 0; i < 1786; i++){
    temp = 0;
    for(int j = 0; j < ("words.txt")[i].len(); j++){
      temp = temp + (int(("words.txt")[i])[j]-96);
    }
    tri = 1;
    add = 1;
    put = false;
    while(tri <= temp){
      tri = (add*(add+1))/2;
      if(tri == temp){
        ans = ans + temp;
      }
      add++;
    }
  }
  cout << ans << endl;
  
}

