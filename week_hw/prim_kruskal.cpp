#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <utility>
#include <map>
using namespace std;

struct edge{
  int start;
  int end;
  int weight;
};

//weighted, undirected graph
class Graph_c{
  //cannot be accessed outside of class
  private:
  
  //adjacency matrix (can only be edited through public methods)
  vector<vector<int> > adjmatrix;
  
  //can be accessed outside of class
  public:
  
  //constructor
  Graph_c(int graphsize){
    for(int i = 0; i < graphsize; ++i){
      vector<int> temp;
      for(int j = 0; j < graphsize; ++j){
        temp.push_back(-1);
      }
      adjmatrix.push_back(temp);
    }
  }

  void clear_graph(){
    for(auto &elem: adjmatrix){
      for(auto &elem2: elem){
        elem2 = -1;
      }
    }
  }

  vector<vector<int> > return_graph(){
    return adjmatrix;
  }

  //print function
  void print_graph(){
    //adjmatrix[i][j] represents weight of vertex i to vertex j
    for(const auto &elem: adjmatrix){
      for(const auto &elem2: elem){
        cout << elem2 << " ";
      }
      cout << endl;
    }
  }

  void add_edge(int vertex1, int vertex2, int weight){
    adjmatrix[vertex1][vertex2] = weight;
    adjmatrix[vertex2][vertex1] = weight;
  }


  //return vector of neighbors belonging to vertex1
  vector<int> vertex_neighbors(int vertex1){
    vector<int> neighbors;
    for(int i = 0; i < adjmatrix.size(); ++i){
      if(adjmatrix[vertex1][i] != -1){
        neighbors.push_back(i);
      }
    }
  }
};

vector<vector<int> > connected_vertices(vector<vector<int> > adjmatrix){
  vector<bool> visited(adjmatrix.size(), false);
  
  vector<vector<int> > subgraphs;

  for(int i = 0; i < visited.size(); ++i){
    if(!visited[i]){
      vector<int> tempvec;

      queue<int> bfsqueue;
      bfsqueue.push(i);
      
      visited[i] = true;

      int cur;
      while(!bfsqueue.empty()){
        
        cur = bfsqueue.front();
        bfsqueue.pop();

        tempvec.push_back(cur);
        
 
        for(int j = 0; j < adjmatrix[cur].size(); ++i){
          if(adjmatrix[cur][j] != -1 && !visited[j]){
            visited[j] = true;
            bfsqueue.push(j);
          }
        }
      }
      subgraphs.push_back(tempvec);
    }
    
  }
  
  return subgraphs;
}

bool compare_edge_weight_des(edge x, edge y){
  return x.weight < y.weight;
}

bool visited_contain(vector<int> visited, int x){
  for(const auto &elem: visited){
    if(x == elem){
      return true;
    }
  }
  return false;
}

bool contain_cycle(vector<vector<int> > adjmatrix){
  vector<int> visited;
  
  queue<pair<int, int> > bfsqueue;
  
  bfsqueue.push(make_pair(0, -1));
  
 
  int cur;
  int parent = -1;

  while(!bfsqueue.empty()){
    cur = bfsqueue.front().first;
    parent = bfsqueue.front().second;
    bfsqueue.pop();
    visited.push_back(cur);
    
    for(int i = 0; i < adjmatrix[cur].size(); ++i){
      if(adjmatrix[cur][i] != -1 && i != parent){
        if(visited_contain(visited, i)){
          //cycle exists
          cout << "cycle found" << endl;
          return true;
        }
        else{
          bfsqueue.push(make_pair(i, cur));
        }
      }
    }
  }
  return false;
}

vector<edge> make_edgelist(vector<vector<int> > adjmatrix){
  vector<edge> edgelist;
  for(int i = 0; i < adjmatrix.size(); ++i){
    for(int j = i + 1; j < adjmatrix[i].size(); ++j){
      if(adjmatrix[i][j] != -1){
        edge tempedge;
        tempedge.start = i;
        tempedge.end = j;
        tempedge.weight = adjmatrix[i][j];
        edgelist.push_back(tempedge);
      }
    }
  }
  return edgelist;
}

vector<vector<int> > make_adjmatrix(vector<edge> edgelist, int vertexnum){
  vector<vector<int> > adjmatrix;
  
  for(int i = 0; i < vertexnum; ++i){
    vector<int> temp(vertexnum, -1);
    adjmatrix.push_back(temp);
  }
  for(auto &elem: edgelist){
    adjmatrix[elem.start][elem.end] = elem.weight;
    adjmatrix[elem.end][elem.start] = elem.weight;
  }
  return adjmatrix;
}

vector<vector<int> > kruskals_alg(vector<vector<int> > adjmatrix){
  cout << "entered kruskals_alg" << endl;
  vector<edge> min_spanning_tree;

  vector<edge> edgelist = make_edgelist(adjmatrix);

  sort(edgelist.begin(), edgelist.end(), compare_edge_weight_des);
  
  for(int i = 0; i < edgelist.size(); ++i){
    cout << edgelist[i].start << ", " << edgelist[i].end  << " ";
  }
  cout << endl;
   
  edge cur;

  for(int i = 0; i < edgelist.size(); ++i){
    cur = edgelist[i];
 
    vector<edge> temp_mst = min_spanning_tree;
    temp_mst.push_back(cur);
    if(!contain_cycle(make_adjmatrix(temp_mst, adjmatrix.size()))){
      cout << "added " << cur.start << ", " << cur.end << endl;
      min_spanning_tree.push_back(cur);
    }   
  }
  return make_adjmatrix(min_spanning_tree, adjmatrix.size());
}

int main(){
  
  Graph_c yeh(7);

  vector<vector<int> > tempvec = yeh.return_graph();
  
  tempvec[0][1] = 7;
  tempvec[1][0] = 7;

  tempvec[0][3] = 5;
  tempvec[3][0] = 5;
  
  tempvec[1][2] = 8;
  tempvec[2][1] = 8;

  tempvec[1][3] = 9;
  tempvec[3][1] = 9;
  
  tempvec[1][4] = 7;
  tempvec[4][1] = 7;
  
  tempvec[2][4] = 5;
  tempvec[4][2] = 5;
  
  tempvec[3][4] = 15;
  tempvec[4][3] = 15;
  
  tempvec[3][5] = 6;
  tempvec[5][3] = 6;
  
  tempvec[4][5] = 8;
  tempvec[5][4] = 8;
  
  tempvec[4][6] = 9;
  tempvec[6][4] = 9;
  
  tempvec[5][6] = 11;
  tempvec[6][5] = 11;
  
  for(int i = 0; i < 7; ++i){
    for(int j = 0; j < 7; ++j){
      cout << tempvec[i][j] << " ";
    }
    cout << endl;
  }

  vector<vector<int> > mst = kruskals_alg(tempvec);

  for(int i = 0; i < mst.size(); ++i){
    for(int j = 0; j < mst[i].size(); ++j){
      cout << mst[i][j] << " ";
    }
    cout << endl;
  }
    
}
