#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){
  string src, f1, f2;
  cout << "src: , f1: , f2: " << endl;
  cin >> src >> f1 >> f2;

  ifstream fin(src);
  ofstream fout1(f1);
  ofstream fout2(f2);

  string src_str;
  string line;
  while(getline(fin, line)){
    src_str += line + "\n";
  }

  fout1 << src_str.substr(0, src_str.length()/2);
  fout2 << src_str.substr(src_str.length()/2, src_str.length()/2);
  return 0;
}
