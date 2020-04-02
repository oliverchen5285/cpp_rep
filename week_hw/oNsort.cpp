//write function that sorts list of ascii characters in O(N) time and O(M) memory
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <utility>
#include <map>
using namespace std;

int main(){
  string in;
  cin >> in;

  map<char, int> dict;

  for(int i = 0; i < in.length(); ++i){
    ++dict[in[i]];
  }
  for(auto &i : dict){
    for(int j = 0; j < i.second; ++j){
      cout << i.first;
    }
  }
  cout << endl;
}





