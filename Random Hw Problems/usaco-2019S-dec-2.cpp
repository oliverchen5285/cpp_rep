#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <vector>
using namespace std;

struct cow{
  int weight;
  int location;
  int direction;
};

void swap(cow& x, cow& y){
  cow z = x;
  x = y;
  y = x;
  
}

int main(){
  int n, l;
  cin >> n >> l;
  vector <int> list[n];
  int totalweight = 0;
  cow line[2000000000];
  line[0] = 1;
  line[l] = 1;
  int tempweight;
  int templocation;
  int tempdirection;
  cow temp;
  for(int i = 0; i < n; ++i){
    cin >> temp.weight >> temp.location >> temp.direction;
    totalweight += temp.weight;
    list.push_back(temp.location);
    line[temp.location * 2].weight = temp.weight;
    line[temp.location * 2].location = temp.location;
    line[temp.location * 2].direction = temp.direction;
  }
  
  int weightsum = 0;
  int meetings = 0;
  while(weightsum < totalweight/2){
    for(int i = 0; i < list.size(); ++i){
      if(line[list[i]+line[list[i]].direction].weight == 0){
        swap(line[list[i]], line[list[i]+line[list[i]].direction]);
      }
      else{
        line[list[i]].direction *= -1;
        line[list[i]+line[list[i]].direction].direction *= -1;

      }

    }
  }
}
