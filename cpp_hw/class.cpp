#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>

using namespace std;

struct node{
  int value;
  //struct node *prev;
  struct node *next;
};


class link{
public:
  node *top;

  link();
  int pop();
  void push(int data);
  void display();
  void reverse();

private:
  
  
};



int main(){
  link a;
  a.push(1);
  a.display();
  a.reverse();
  a.display();
  a.push(2);
  a.push(3);
  a.push(4);
  a.display();
  a.reverse();
  a.display();
  a.pop();
  a.display();
}

link::link(){
  top = NULL;
}

int link::pop(){
  if(top != NULL){
    int temp = top->value;
    top = top->next;
    cout << "popped " << temp << endl;
    return temp;
  }
  cout << "list empty, returning -1" << endl;
  return -1;
}

void link::push(int data){
  node *temp = new node;
  temp->value = data;
  temp->next = top;
  top = temp;
  cout << "pushed " << data << endl;
}

void link::display(){
  node *temp = top;
  cout << "display: " << endl;
  while(temp != NULL){
    cout << temp->value << endl;
    temp = temp->next;
  }
}


void link::reverse(){
  node *cur = NULL;
  node *temp = top;
  node *tempnext;
  cout << "reverse: " << endl;
  while(temp!= NULL){
    tempnext = temp->next;
    temp->next = cur;
    cur = temp;
    temp = tempnext;
  }
  top = cur;
}