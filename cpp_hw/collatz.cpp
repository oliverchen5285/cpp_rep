#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <map>
using namespace std;

map<int, int> memo;


int powof(int x){
  int ans = 1;
  for(int i = 0; i < x; ++i){
    ans *= 2;
  }
  return ans;
}


vector<pair<int, int> > make_pow_two(){
  vector<pair<int, int> > ans;
  for(int i = 1; i < 31; ++i){
    pair<int, int> temp;
    temp.first = powof(i);
    temp.second = i;
    ans.push_back(temp);
  }
  return ans;

}


int findsteps(int x){
  if(memo.find(x) == memo.end()){
      int next = (x%2 == 0) ? x/2 : x*3 + 1;
      int ans = findsteps(next) + 1;
      memo.insert(pair<int, int>(x, ans));
  }
  return memo[x];
}


int main(){
  memo[1] = 0;
  int n;
  cin >> n;

  int temp = n;
  
  int step = 0;
  

    


  //iterative
  while (temp != 1){
    if(temp % 2 == 0){
      temp = temp / 2;
    }
    else{
      temp = temp * 3 + 1;
    }
    cout << temp << endl;
    ++step;
  }
  cout << n << ": " << step << endl;

  

  //memo
  for(int i = 1; i <= n; ++i){
    cout << i << ": " << findsteps(i) << endl;
  }
  for(const pair<int, int> &kv : memo){
    cout << kv.first << " " << kv.second << endl;
  }





  //dp 
  /*
  don't know how I would implement dp, because I don't know how the structure of the table would look like
  one idea is to make a vector of vectors, where each vector contains a reverse collatz sequence (1, 2, 4, 8, 16, 32, ...)
  make a new vector every time you get the opportunity to subtract 1 and divide by 3 (1, 2, 4 -> 1)
  but every sequence could be infinite (you multiply by 2 indefinitely across basically infinite lists) and there is no guarantee to reach n in certain time
  you cannot just stop the sequence at n because for all odd n you have to first reach n*3 + 1 (which may require an even greater upper bound)
  
  soooo really there is no exact upper bound for a dp table

  basically this method won't work (try everything)
  gosh dag nab it darny dang doosh
  */
  
  
  
}

