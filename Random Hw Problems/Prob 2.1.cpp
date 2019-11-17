#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct num{
    int first;
    int second;
    bool visited;
};

bool help(num x, num y){
    return x.first < y.first;
}

bool help2(num x, num y){
    return x.second < y.second;
}
int main(){
  int n;
  cin >> n;
  num a[n];
  for(int i = 0; i < n; i++){
      cin >> a[i].first;
      a[i].second = i;
      a[i].visited = false;
  }
  sort(a, a+n, help);
  for(int i = 0; i < n; i++){
      a[i].first = i;
  }
  
  sort(a, a+n, help2);
    for(int i = 0; i < n; ++i){
      cout << a[i].first << " ";
  }
  cout << endl;
  int ans = 0;
  int origin;
  int cur;

  for(int i = 0; i < n; ++i){
    if(a[i].first != i && a[i].visited == false){
      origin = i;
      cur = i;
      for(int j = 0; j < n; ++j){
        if(cur == origin && j!= 0){
          ans = ans + j-1;
          cout << "end of loop" << endl;
          break;
        }
        a[cur].visited = true;
        cout << a[cur].first << "," << a[cur].second << "(" << a[cur].visited << ")  ";
        cur = a[a[cur].first].second;
        a[cur].visited = true;
        
      }
      cout << endl;
    }

  }

  cout << ans << endl;
  
}


/*
8 3 2 0 5
1 2 3 4 5
0 2 3 5 8
4 3 2 5 1
0 1 2 3 4
4 3 2 5 1

4 2 1 0 3
0 1 2 3 4
*/
/*
c++ problems

1. (1s)

On a black windy night, there are n people who want to cross the bridge. They only have one light. The bridge is so narrow that can only allow two people to cross the bridge at a time. Now tell you the time it takes for everyone to cross the bridge and ask you the least time  needed to make all the people cross the bridge. If two people have different bridge crossing times, the time they spend crossing the bridge is calculated according to the time of the slower .

Input :
Enter the first line of an integer n
Enter the n integer in the second line to indicate the time required for the n person to cross the bridge.

Output :
Output a line containing an integer indicating the minimum time required for everyone to cross the bridge

Sample input:
5
1 3 6 8 12


Sample output:
29


2. (I think 1s)

Farmer John is attempting to take a photograph of his herd of cows. From past experience, he knows this particular endeavor never usually ends well.
This time, Farmer John has purchased an expensive drone in order to take an aerial photo. To make the photo look as good as possible, he wants his cows all to be facing the same direction when the photo is taken. The cows are currently arranged in an N×N grid (2≤N≤1000) inside a fenced-in square pasture, for example:

RLR
RRL
LLR
Here, an 'R' means a cow facing right, and an 'L' means a cow facing left. Since the cows are packed together, Farmer John cannot walk up to an individual cow to make it turn around. All he can do is shout at any row or column of cows to turn around, causing L's to change to R's and R's to L's within the row or column in question. Farmer John can yell at as many rows or columns as he wants, even at the same row or column more than once.

As expected, Farmer John observes that he is unable to make his cows all face one common direction. The best he can do is get all but one of the cows to face the same direction. Please determine the identity of such a cow.

INPUT FORMAT (file leftout.in):
The first line contains N. The next N lines describe rows 1…N in the grid of cows, each containing a string of length N.
OUTPUT FORMAT (file leftout.out):
Print the row and column index of a cow such that if that cow were flipped, Farmer John could make all his cows face the same direction. If no such cow exists, print -1. If multiple such cows exist, print the one with the smallest row index, or if multiple such cows have the same smallest row index, print the one with the smallest column index.
SAMPLE INPUT:
3
RLR
RRL
LLR
SAMPLE OUTPUT:
1 1
In the example above, the cow in row 1, column 1 (the upper-left corner) is the offending cow, since Farmer John can shout at row 2 and column 3 to make all other cows face left, with just this cow facing right.

Problem credits: Brian Dean



*/
