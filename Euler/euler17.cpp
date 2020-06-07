#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int numLet(int n){
  unordered_map<int, int> uni_let = {
    {1, 3}, //one
    {2, 3}, //two
    {3, 5}, //three
    {4, 4}, //four
    {5, 4}, //five
    {6, 3}, //six
    {7, 5}, //seven
    {8, 5}, //eight
    {9, 4} //nine
  };
  unordered_map<int, int> ten_let = {
    {10, 3}, //ten
    {11, 6}, //eleven
    {12, 6}, //twelve
    {13, 8}, //thirteen
    {14, 8}, //fourteen
    {15, 7}, //fifteen
    {16, 7}, //sixteen
    {17, 9}, //seventeen
    {18, 8}, //eighteen
    {19, 8} //nineteen
  };
  unordered_map<int, int> dec_let = {
    {20, 6}, //twenty
    {30, 6}, //thirty
    {40, 5}, //forty
    {50, 5}, //fifty
    {60, 5}, //sixty
    {70, 7}, //seventy
    {80, 6}, //eighty
    {90, 6} //ninety
  };
  int letters = 0;
  if(n >= 1000){
    letters += uni_let[n / 1000];
    letters += 8; //thousand
  }
  if(n%1000 >= 100){
    letters += uni_let[(n % 1000) / 100];
    letters += 7; //hundred
  }
  if(n % 100 > 0 && (n % 10000) - n % 100){
    letters += 3; //and
  }
  if(n%100 >= 10){
    if(n%100 < 20){
      letters += ten_let[n % 100];
    }
    else{
      letters += dec_let[(n % 100) - (n % 10)];
    }
  }
  if(n % 10 > 0 && (n % 100 >= 20 || n % 100 < 10)){
    letters += uni_let[n % 10];
  }
  return letters;
}

int allWords(int n){
  int sum = 0;
  for(int i = 1; i <= n; ++i){
    int temp_ans = numLet(i);
    cout << i << ", " << temp_ans << endl;
    sum += temp_ans;
  }
  return sum;
}

int main(){
  cout << allWords(1000) << endl;
}
