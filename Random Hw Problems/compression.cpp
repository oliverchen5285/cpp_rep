#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <map>
using namespace std;

class node{
public:
  double prob;
  int value;
  string bitrep;
  
  class node *left;
  class node *right;

  node();
};

bool compareprob(node *x, node *y){
  return x->prob <= y->prob;
}


node::node()
{
  bitrep = "";
  left = NULL;
  right = NULL;
}

void compress(vector<node *> &tree){
  for(int i = 0; i < tree.size(); ++i){
    cout << "debug1: " << tree[i]->prob << endl;
  }
  cout << endl;

  sort(tree.begin(), tree.end(), compareprob);
  for(int i = 0; i < tree.size(); ++i){
    cout << "debug2: " << tree[i]->prob << endl;
  }
  cout << endl;
  
  node *temp;
  temp = new node;
  temp->prob = tree[0]->prob + tree[1]->prob;
  temp->value = -1;
  
  temp->left = tree[0];
  temp->right = tree[1];

  tree.erase(tree.begin());

  for(int i = 0; i < tree.size(); ++i){
    cout << "debug3: " << tree[i]->prob << endl;
  }
  cout << endl;

  tree.erase(tree.begin());
 
  for(int i = 0; i < tree.size(); ++i){
    cout << "debug4: " << tree[i]->prob << endl;
  }
  cout << endl;


  tree.push_back(temp);

  for(int i = 0; i < tree.size(); ++i){
    cout << "debug5: " << tree[i]->prob << endl;
  }
  cout << endl;


}


void genbitrep(node *start, map<int, string> &bitdict){
  
  bitdict.insert(pair<int, string> (start->value, start->bitrep));
  //cout << start->bitrep << endl;

  if(start->left != NULL){
    start->left->bitrep.append(start->bitrep + "1");
    genbitrep(start->left, bitdict);
  }
  if(start->right != NULL){
    start->right->bitrep.append(start->bitrep + "0");
    genbitrep(start->right, bitdict);
  }

  return;
}



int main(){
  int n;
  cin >> n;
  vector<node *>leaf;

  
  
  for(int i = 0; i < n; ++i){
    node *temp = new node;
    cin >> temp->prob;
    cin >> temp->value;
    cout << temp->prob << ", " << temp->value << endl;

    leaf.push_back(temp);
    cout << "pushed temp" << endl;
  }

  cout << "finish" << endl; 

  for(int i = 0; i < n-1; ++i){
    compress(leaf);
  }

  cout << "compress done" << endl;

  map<int, string> bitdict;
  genbitrep(leaf[0], bitdict);

  cout << "genbitrep done" << endl;

  for(int i = 0; i < n; ++i){
    cout << (bitdict.find(i+1))->second << endl;
  }
  

  
}


