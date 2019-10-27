#include <iostream>
#include <string>
using namespace std;

int main()
{
  bool rel;
  for(int i = 1; i < 22; i = i + 2){
    for(int j = 2; j <= 22; j = j + 2){
      rel = true;
      for(int k = 2; k <= min(i, j); k++){
        if(j%k == 0 && i%k == 0){
          rel = false;
        }
      }
      if(rel == true){
        int temp = (max(i, j)*max(i, j) - min(i, j)*min(i, j))+(2*i*j)+(i*i + j*j);
        if(1000%temp == 0){
          cout << (max(i, j)*max(i, j) - min(i, j)*min(i, j)) << endl;
          cout << (2*i*j) << endl;
          cout << (i*i + j*j) << endl;
          cout << i << " " << j << endl;
          long ans = (1000/temp)*(1000/temp)*(1000/temp)*(max(i, j)*max(i, j) - min(i, j)*min(i, j))*(2*i*j)*(i*i + j*j);
          cout << ans << endl;
        }
      }
    }
  }
}

