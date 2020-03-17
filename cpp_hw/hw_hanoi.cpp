#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct from{
    int num;
    string start;
    string end;
};



int main()
{
  vector<from> pegs;
  vector<from> copy;
  int n;
  cin >> n;
  from temp;
  temp.num = 1;
  temp.start = "A";
  temp.end = "B";
  pegs.push_back(temp);
  
  for(int i = 1; i < n; i++){
      copy.clear();
      for(int j = 0; j < pegs.size(); j++){
          copy.push_back(pegs[j]);
      }
      pegs.clear();
      for(int j = 0; j < copy.size(); j++){
          temp.num = copy[j].num;
          if(copy[j].start == "C"){
              temp.start = "B";
          }
          if(copy[j].end == "C"){
              temp.end = "B";
          }
          if(copy[j].start == "B"){
              temp.start = "C";
          }
          if(copy[j].end == "B"){
              temp.end = "C";
          }
          if(copy[j].start == "A"){
              temp.start = "A";
          }
          if(copy[j].end == "A"){
              temp.end = "A";
          }
          pegs.push_back(temp);
      }
      temp.num = i+1;
      temp.start = "A";
      temp.end = "B";
      pegs.push_back(temp);
      for(int j = 0; j < copy.size(); j++){
          temp.num = copy[j].num;
          if(copy[j].start == "A"){
              temp.start = "C";
          }
          if(copy[j].end == "A"){
              temp.end = "C";
          }
          if(copy[j].start == "C"){
              temp.start = "A";
          }
          if(copy[j].end == "C"){
              temp.end = "A";
          }
          if(copy[j].start == "B"){
              temp.start = "B";
          }
          if(copy[j].end == "B"){
              temp.end = "B";
          }
          pegs.push_back(temp);
      }
  }
  cout << pegs.size() << endl;

  vector <int> left;
  vector <int> middle;
  vector <int> right;
  for(int i = n-1; i <= 0; i++){
      left.push_back(i+1);
  }

  char letters[3] = {'A','B','C'};

  for(int i = 0; i < pegs.size(); i++){
      cout << pegs[i].num << " " << pegs[i].start << " " << pegs[i].end << endl;
      
  }
  vector<int>peg1;
  vector<int>peg2;
  vector<int>peg3;
  for(int i = 0; i < n; i++){
    peg1.push_back(n-i);
  }
  int curgive; 
  int curtake; 
  int trans;

  for(int i = 0; i < pegs.size(); i++){
    if(pegs[i].start == "A"){
      trans = peg1.back();
      if(pegs[i].end == "B"){
        peg1.pop_back();
        peg2.push_back(trans);
      }
      else if(pegs[i].end == "C"){
        peg1.pop_back();
        peg3.push_back(trans);
      }
    }
    if(pegs[i].start == "B"){
      trans = peg2.back();
      if(pegs[i].end == "A"){
        peg2.pop_back();
        peg1.push_back(trans);
      }
      else if(pegs[i].end == "C"){
        peg2.pop_back();
        peg3.push_back(trans);
      }
    }
    if(pegs[i].start == "C"){
      trans = peg3.back();
      if(pegs[i].end == "A"){
        peg3.pop_back();
        peg1.push_back(trans);
      }
      else if(pegs[i].end == "B"){
        peg3.pop_back();
        peg2.push_back(trans);
      }
    }
    cout << endl << "1: ";
    for(int i = 0; i < peg1.size(); i++){
      cout << peg1[i] << " ";
    }
    cout << endl << "2: ";
    for(int i = 0; i < peg2.size(); i++){
      cout << peg2[i] << " ";
    }
    cout << endl << "3: ";
    for(int i = 0; i < peg3.size(); i++){
      cout << peg3[i] << " ";
    }
  }
  cout << endl;
  
}