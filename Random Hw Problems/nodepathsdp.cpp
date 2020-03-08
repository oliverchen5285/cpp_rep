#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <utility>
using namespace std;

struct edge{
  int start;
  int end;
};

int main(){
  //assume directed acyclic graph
  //number of paths from node 0 to node N-1 (first node is node 0)
  //dp
  
  int nodenum, edgenum;
  cin >> nodenum >> edgenum;
  
  vector<edge> edgevect;
  
  for(int i = 0; i < edgenum; ++i){
    edge temp;
    cin >> temp.start >> temp.end;
    
    edgevect.push_back(temp);
  }
  
  //# of paths from node 0 to dptable[x][y]
  //measured by nodenum and steps
  int dptable[nodenum][edgenum];

  
  
  for(int steps = 0; steps < edgenum; ++steps){
    for(int curnode = 0; curnode < nodenum; ++curnode){
      if(steps == 0 && curnode == 0){
        //1 way to reach node 0 with 0 steps
        dptable[steps][curnode] = 1;
      }
      else if(steps == 0 && curnode != 0){
        //0 ways to reach node 1 -> N with 0 steps (start at node 0)
        dptable[steps][curnode] = 0;
      }
      else if(steps != 0 && curnode == 0){
        //0 ways to stay at node 0 with 1+ steps
        dptable[steps][curnode] = 0;
      }
      else{
        //set # of paths to 0 first, then add for every previous node
        dptable[steps][curnode] = 0;
        
        //iterate through previous nodes (step - 1)
        for(int prevnode = 0; prevnode < nodenum; ++prevnode){
          if(dptable[steps-1][prevnode] > 0 && prevnode != curnode){
            //if different previous node is possible
            //search edgevect for prevnode -> curnode
            for(int curedge = 0; curedge < edgenum; ++curedge){
              if(edgevect[curedge].start == prevnode && edgevect[curedge].end == curnode){
                dptable[steps][curnode] += dptable[steps-1][prevnode];
              }
            }
          }
        }
      }
    }
  }
  cout << "debug: dp table " << endl;
  for(int i = 0; i < edgenum; ++i){
    for(int j = 0; j < nodenum; ++j){
      cout << dptable[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
  
  int ans = 0;
  
  //return # of ways to reach node N-1 with 0 steps, 1 step, 2 steps, etc.
  for(int steps = 0; steps < edgenum; ++steps){
    ans += dptable[steps][nodenum-1];
  }
  
  cout << "# of paths to N-1 from 0: " << ans << endl;

  
}

