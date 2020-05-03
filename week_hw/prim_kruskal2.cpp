#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <utility>
#include <map>
using namespace std;

struct edge_s{
  pair<int, int> vertice;
  int cost;
};


bool compare_edge_inc(edge_s x, edge_s y){
  return x.cost < y.cost;
}

class Graph_c{
  private:
    vector<edge_s> edgevec; // vector of edges
    vector<int> treegroupvec; //vector of vertices' treegroups(vi = i)
  public:
    //initialize functions
    Graph_c(int vertice_num){
      for(int i = 0; i < vertice_num; ++i){
        treegroupvec.push_back(i);
      }
    }
    void push_edge(edge_s cur_edge){
      edgevec.push_back(cur_edge);
    }

    //functions for edgevec
    void sort_edgevec_inc(){
      sort(edgevec.begin(), edgevec.end(), compare_edge_inc);
    }
    int edgevec_size(){
      return edgevec.size();
    }
    edge_s edgevec_elem(int index){
      return edgevec[index];
    }

    //functions for treegroupvec
    int treegroupvec_elem(int index){
      return treegroupvec[index];
    }
    bool form_cycle(edge_s cur_edge){
      return treegroupvec[cur_edge.vertice.first] == treegroupvec[cur_edge.vertice.second];
    }
    void combine_tree(edge_s cur_edge){
      int new_tree = treegroupvec[cur_edge.vertice.first];
      int old_tree = treegroupvec[cur_edge.vertice.second];

      for(auto &elem: treegroupvec){
        if(elem == old_tree){
          elem = new_tree;
        }
      }
      return;
    }
    
};

struct end_cost_s{
  int end;
  int cost;
};

bool compare_end_cost_s_inc(end_cost_s x, end_cost_s y){
  return x.cost < y.cost;
}

class Graph2_c{
  private:
    vector<vector<end_cost_s> > edgelist;
  public:
    void sort_edgelist_inc(int index){
      sort(edgelist[index].begin(), edgelist[index].end(), compare_end_cost_s_inc);
    }
    int vertice_num(){
      return edgelist.size();
    }
    bool invec(int elem, vector<int> vec){
      for(int i = 0; i < vec.size(); ++i){
        if(elem == vec[i]){
          return true;
        }
      }
      return false;
    }
    edge_s min_edge_edgelist(int edgeindex, vector<int> visited_vertices){
      edge_s minedge;
      minedge.vertice.first = -1;
      minedge.vertice.second = -1;
      minedge.cost = -1;
      for(int i = 0; i < edgelist[edgeindex].size(); ++i){
        if((minedge.cost == -1 || edgelist[edgeindex][i].cost < minedge.cost) && !invec(edgelist[edgeindex][i].end, visited_vertices)){
          minedge.vertice.first = edgeindex;
          minedge.vertice.second = edgelist[edgeindex][i].end;
          minedge.cost = edgelist[edgeindex][i].cost;
        }
      }
      return minedge;
    }
};

pair<vector<edge_s>, int> kruskals(Graph_c graph){

  vector<edge_s> mst;
  int mst_weight = 0;

  graph.sort_edgevec_inc();
  
  for(int i = 0; i < graph.edgevec_size(); ++i){
    if(!graph.form_cycle(graph.edgevec_elem(i))){
      cout << "found new edge" << endl;
      mst_weight += graph.edgevec_elem(i).cost;
      mst.push_back(graph.edgevec_elem(i));
      graph.combine_tree(graph.edgevec_elem(i));
    }
  }
  
  return {mst, mst_weight};
}

void remove_elem(vector<int> &elemvec, int x){
  elemvec.erase(remove(elemvec.begin(), elemvec.end(), x), elemvec.end());
}

pair<vector<edge_s>, int> prims(Graph2_c graph){
  
  vector<int> visited_vertices;
  vector<edge_s> mst;
  int mst_weight = 0;
  
  vector<int> unvisited_vertices;
  for(int i = 0; i < graph.vertice_num(); ++i){
    unvisited_vertices.push_back(i);
  }

  visited_vertices.push_back(0);
  remove_elem(unvisited_vertices, 0);

  while(!unvisited_vertices.empty()){
    edge_s min_edge;
    min_edge.vertice.first = -1;
    min_edge.vertice.second = -1;
    min_edge.cost = -1;
    for(int i = 0; i < visited_vertices.size(); ++i){
      edge_s temp_edge = graph.min_edge_edgelist(visited_vertices[i], visited_vertices);
      if(min_edge.cost == -1 || temp_edge.cost < min_edge.cost){
        min_edge = temp_edge;
      }
    }
    mst.push_back(min_edge);
    mst_weight += min_edge.cost;

    remove_elem(unvisited_vertices, min_edge.vertice.second);
    visited_vertices.push_back(min_edge.vertice.second);
    
  }
  
  return {mst, mst_weight};
}

int main(){
  Graph_c graph(9);
  
  vector<pair<int, int> > testvertices = {
   {7, 6},
   {8, 2},
   {6, 5},
   {0, 1},
   {2, 5},
   {8, 6},
   {2, 3},
   {7, 8},
   {0, 7},
   {1, 2},
   {3, 4},
   {5, 4},
   {1, 7},
   {3, 5}
  };
  vector<int> testweights = {1, 2, 2, 4, 4, 6, 7, 7, 8, 8, 9, 10, 11, 14};

  for(int i = 0; i < 14; ++i){
    edge_s temp_edge;
    temp_edge.vertice = testvertices[i];
    temp_edge.cost = testweights[i];
    graph.push_edge(temp_edge);
  }

  pair<vector<edge_s>, int> mst = kruskals(graph);
  
  cout << mst.second << endl;

  









}
