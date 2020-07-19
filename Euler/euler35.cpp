#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <string>
using namespace std;

bool is_prime(const int n){
  for(int i = 2; i < (int)sqrt(n) + 1; ++i){
    if(n % i == 0){
      return false;
    }
  } 
  return true;
}

vector<int> rotations(int n){
  vector<int> ans;
  string str_ans = to_string(n);
  string temp = str_ans;
  for(int i = 1; i < str_ans.length(); ++i){
    str_ans = temp;
    for(int j = 0; j < temp.length(); ++j){ 
      temp[j] = str_ans[(j+1)%temp.length()];
    }
    ans.push_back(stoi(temp, nullptr));
  }
  return ans;
}

int circ_primes(const int n){
  vector<bool> prime_vec(n, true); //generate all primes using sieve?
  prime_vec.front() = false;
  for(int i =0 ; i < n; ++i){
    if(prime_vec[i]){
      for(int j = i + (i + 1); j < n; j += (i + 1)){
        prime_vec[j] = false;
      }
    }
  }
  int ans = 0;
  for(int i = 0; i < n; ++i){
    if(prime_vec[i]){
      bool circ = true;
      /*
      do{
        if(!is_prime(stoi(num, nullptr))){
          circ = false;
          break;
        }
      } while(next_permutation(num.begin(), num.end()));
      */
      for(const auto &elem: rotations(i + 1)){
        if(!is_prime(elem)){
          circ = false;
          break;
        }
      }
      if(circ){
        cout << i + 1 << endl;
        ++ans;
      }
    }
  }
  return ans;
}

int main(){
  cout << circ_primes(1000000) << endl;
  //for(const auto &elem: rotations(12345)){
  //  cout << elem << endl;
  //}
}
