#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <map>
using namespace std;

struct edge{
  int start;
  int end;
};

bool contains(vector<int> visited, int key){
  for(int i = 0; i < visited.size(); ++i){
    if(key == visited[i]){
      return true;
    }
  }
  return false;
}

vector<int> findend(vector<edge> edges, vector<int> visited, int key){
  vector<int> ans;
  for(int i = 0; i < edges.size(); ++i){
    cout << "searching edges: " << edges[i].start << ", " << edges[i].end;
    cout << endl;
    if(edges[i].start == key && contains(visited, edges[i].end) == false){
      cout << "found " << edges[i].end << endl;
      ans.push_back(edges[i].end);
    }
  }
  cout << "next nodes: " << key << endl;
  for(int i = 0; i < ans.size(); ++i){
    cout << ans[i] << " ";
  }
  cout << endl;
  return ans;
}

int dfs(vector<edge> edges, int cur, int dest, vector<int> visited, int path){
  visited.push_back(cur);
  vector<int> ans = findend(edges, visited, cur);
  for(int i = 0; i < ans.size(); ++i){
    if(ans[i] == dest){
      ++path;
    }
    else{
      visited.push_back(ans[i]);
      path = dfs(edges, ans[i], dest, visited, path);
      visited.pop_back();
      
    }
  }
  return path;
  
}

int main(){
  int nodenum, edgenum;

  cin >> nodenum >> edgenum;
  int endnode = nodenum - 1;

  cout << nodenum << " " << edgenum << endl;

  vector<edge> edges;
  
  for(int i = 0; i < edgenum; ++i){
    edge temp;
    cin >> temp.start >> temp.end;
    cout << temp.start << " " << temp.end << endl;
    edges.push_back(temp);
  }

  int paths = 0;

  queue<int> bfsqueue;

  bfsqueue.push(0);

  vector<int> visited;

  cout << "edges: " << endl;
  for(int i = 0; i < edges.size(); ++i){
    cout << "(" << edges[i].start << ", " << edges[i].end << ") ";
  }
  cout << endl;
  
  while(!bfsqueue.empty()){
    int curnode = bfsqueue.front();
    visited.push_back(curnode);
    bfsqueue.pop();
    cout << "cur: " << curnode << endl;
    
    vector<int> ans = findend(edges, visited, curnode);
    
    for(int i = 0; i < ans.size(); ++i){
      if(ans[i] == endnode){
        ++paths;
      }
      else{
        bfsqueue.push(ans[i]);
        
      }
    }
    
  }
  vector<int> tempvisited;
  cout << paths << endl;
  cout << dfs(edges, 0, endnode, tempvisited, 0) << endl;
  
  
}

