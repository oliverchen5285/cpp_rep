#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <utility>
#include <map>
using namespace std;

/*
bool operator<(const int& x, const int& y){
  return x < y;
}
*/

int main(){
  //sort DAG (directed acyclic graph) in topogical ordering
  int nodenum, edgenum;

  cin >> nodenum >> edgenum;

  vector<pair<int, int> > edgevec;

  for(int i = 0; i < edgenum; ++i){
  	pair<int, int> temp;
  	cin >> temp.first >> temp.second;

  	edgevec.push_back(temp);
  }
  /*
  vector<int> nodeways;
  vector<int> readynodes;
  vector<int> incoming;
  vector<vector<int> > from;
  for(int i = 0; i < edgenum; ++i){
  	incoming[edgevec[i].start] += 1;
  	from[edgevec[i].start].push_back(e.end());
  }

  while(!readynodes.empty()){
  	//take next node from ready nodes
  	int curnode = readynodes.back();
  	readynodes.pop_back();

  	//take all of the outgoing edges from that node
  	for(int i = 0; i < )
  }
  */

  map<int, int> ToNodeCount;
  for(int i = 0; i < edgenum; ++i){
    if(ToNodeCount.find(edgevec[i].first) == ToNodeCount.end()){
        ToNodeCount[edgevec[i].first] = 0;

    }
  	if(ToNodeCount.find(edgevec[i].second) == ToNodeCount.end()){
        ToNodeCount[edgevec[i].second] = 1;
  	}
    else{
        ++ToNodeCount[edgevec[i].second];
    }
  }
  cout << "debug: map" << endl;
  for(auto elem : ToNodeCount){
    cout << elem.first << ", " << elem.second << endl;
  }
  cout << endl;

  //pqueue just lets you sort same-level nodes 
  queue<int> nodequeue;
  //priority_queue<int> nodequeue;

  for(auto &elem : ToNodeCount){
    if(elem.second == 0){
        cout << "added " << elem.first << endl;
        nodequeue.push(elem.first);
        elem.second = -10;
    }
  }

  vector<int> ansorder;
  int curnode;

  if(nodequeue.empty()){
    cout << "empty" << endl;
  }

  while(!nodequeue.empty()){

    curnode = nodequeue.front();
    nodequeue.pop();

    cout << "curnode: " << curnode << endl;

    ansorder.push_back(curnode);

    for(int i = 0; i < edgevec.size(); ++i){
        if(edgevec[i].first == curnode){
            ToNodeCount[edgevec[i].second] -= 1;
        }
    }
    cout << "debug: map" << endl;
    for(auto elem : ToNodeCount){
        cout << elem.first << ", " << elem.second << endl;
    }
    cout << endl;


    for(auto &elem : ToNodeCount){
        if(elem.second == 0){
            cout << "added " << elem.first << endl;
            nodequeue.push(elem.first);
            elem.second = -10;
        }
    }

    cout << "debug: map" << endl;
    for(auto elem : ToNodeCount){
        cout << elem.first << ", " << elem.second << endl;
    }
    cout << endl;

  }

  for(auto i : ansorder){
    cout << i << " ";
  }
  cout << endl;




}

