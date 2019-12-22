#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>

//type define

using namespace std;

struct link{
  int value;
  struct link *next;
};

link *top1 = NULL; 
link *top2 = NULL;

void push(int x){
  link *temp = (link*) malloc(sizeof(link));
  temp-> value = x;
  temp-> next = top1;
  top1 = temp;
  cout << "push: " << top1 -> value << endl;
}

void push2(int x){
  link *temp = (link*) malloc(sizeof(link));
  temp-> value = x;
  temp-> next = top2;
  top2 = temp;
  cout << "push: " << top2 -> value << endl;
}

void pop(){
  if(top1 != NULL){
    cout << "pop: " << top1 -> value << endl;
    top1 = top1 -> next;
  }
}

void pop2(){
  if(top2 != NULL){
    cout << "pop2: " << top2 -> value << endl;
    top2 = top2 -> next;
  }
}

void reverse(){
  link *index;
  index = top1;
  
  link *index2;
  index2 = top2;
  while(index2 != NULL){
    pop2();
  }
  while(index != NULL){
    push2(index -> value);
    index = index -> next;
  }
  link *temp;
  temp = top1;
  top1 = top2;
  top2 = temp;
}



int main(){
  push(1);
  push(2);
  push(3);
  reverse();
  pop();
  pop();
  pop();
}