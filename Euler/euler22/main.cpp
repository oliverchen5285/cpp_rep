#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

ifstream fin("names.txt");

vector<string> split_names(string &names){
  vector<string> names_vec;
  string name = "";
  for(const auto &elem: names){
    if(elem == ','){
      names_vec.push_back(name);
      name = "";
    }
    else{
      name += elem;
    }
  }
  return names_vec;
}

long score(string &name, int index){ //error message "expects l-value" when I try to pass in int by reference -- does &index mean pointer?
  //A = 65
  long ans = 0;
  for(int i = 1; i < name.size() - 1; ++i){
    ans += (int)name[i] - 64;
  }
  ans *= index;
  return ans;
}

long score_sum(vector<string> names_vec){
  long ans = 0;
  for(int i = 0; i < names_vec.size(); ++i){
    long temp_score = score(names_vec[i], i+1);
    ans += temp_score;
    cout << names_vec[i] << ", " << temp_score << ", " << ans << endl;
  }
  return ans;
}


int main() {

  string names;
  fin >> names;
  vector<string> names_vec = split_names(names);
  sort(names_vec.begin(), names_vec.end());
  /*
  cout << "size: " << names_vec.size() << endl;
  for(int i = 0; i < 50; ++i){
    cout << names_vec[i] << endl;
  }
  cout << endl;
  */
  cout << score_sum(names_vec);
}

