#include <iostream>
using namespace std;

long long tri(const int n){
  return (n * (n + 1))/2;
}

long long pent(const int n){
  return (n * (3*n - 1))/2;
}

long long hex(const int n){
  return (n * (2*n - 1));
}

long long tri_pent_hex(){
  int tri_index = 285 + 1;
  int pent_index = 165 + 1;
  int hex_index = 143 + 1;
  
  long long tri_cur = tri(tri_index);
  long long pent_cur = pent(pent_index);
  long long hex_cur = hex(hex_index);
  while(true){
    cout << tri_index << ", " << pent_index << ", " << hex_index << endl;
    cout << tri_cur << ", " << pent_cur << ", " << hex_cur << endl << endl;    
    if(tri_cur == pent_cur && pent_cur == hex_cur){
      break;
    }
    if(tri_cur <= pent_cur && tri_cur <= hex_cur){ //one of the smallest
      ++tri_index;
      tri_cur = tri(tri_index);
    }
    else if(pent_cur <= tri_cur && pent_cur <= hex_cur){
      ++pent_index;
      pent_cur = pent(pent_index);
    }
    else{
      ++hex_index;
      hex_cur = hex(hex_index);
    }
  }
  return tri_cur;
}

int main(){
  cout << tri_pent_hex() << endl;
  return 0;
}
