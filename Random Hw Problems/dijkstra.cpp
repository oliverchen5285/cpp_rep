#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>
using namespace std;

struct highway{
  int start;
  int end;
  int time;
};

bool operator<(const pushin &x, const pushin &y){
  return nodetime[x-1] < nodetime[y-1];
}

int main()
{
  int n;
  cin >> n;
  highway nodes[n];
  for(int i = 0; i < n; ++i){
    cin >> nodes[i].start >> nodes[i].end >> nodes[i].time;
  }
  int nodetime[n];
  nodetime[0] = 0;
  for(int i = 1; i < n; i++){
    nodetime[i] = -1;
  }

  set<int> visited;
  priority_queue<int> pqueue;

  pqueue.push(n - 1);
  int cur;
  bool contain;
  
  while(!pqueue.empty()){
    cur = pqueue.top();
    cout << "cur " << cur << endl;
    pqueue.pop();
    visited.insert(cur);
    for(int i = 0; i < n; i++){
      if(nodes[i].start == cur){
        if(nodetime[nodes[i].end-1] > nodes[i].time + nodetime[cur-1] || nodetime[nodes[i].end-1] == -1){
          nodetime[nodes[i].end-1] = nodes[i].time + nodetime[cur-1];
          cout << " - " << nodes[i].end << " -> " << nodetime[nodes[i].end-1] << endl;
        }
        if(!visited.count(nodes[i].end)){
          pqueue.push(nodes[i].end);
          cout << " - " << "pushed " << nodes[i].end << endl;
        }
      }
    }
  }
  cout << endl;
  for(int i = 0; i < n; i++){
    cout << nodetime[i] << " ";
  }
  cout << endl;
  cout << nodetime[n-1] << endl;
}

