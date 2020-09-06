#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
  string f1, f2, tgt;
  cout << "f1: , f2: , tgt: " << endl;
  cin >> f1 >> f2 >> tgt;  

  ifstream fin1(f1);
  ifstream fin2(f2);
  ofstream fout(tgt);

  string f1_str;
  string line;
  while(getline(fin1, line)){
    f1_str += line + "\n";
  }

  string f2_str;
  while(getline(fin2, line)){
    f2_str += line + "\n";
  }
  
  string tgt_str; //add to string and then fout all at once because fout overwrites
  for(int i = 0; i < f1_str.length(); ++i){
    int digit = (int)f1_str[i] ^ (int)f2_str[i];
    tgt_str += (char)digit;
  }

  fout << tgt_str;
  return 0;
}
