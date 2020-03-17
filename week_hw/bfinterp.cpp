#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>

using namespace std;

//BrainF interpreter written in C++

int main(){
  cout << "find me4" << endl;
  int data[10];
  for(int i = 0; i < 10; ++i){
    data[i] = 0;
  }
  string instr;
  getline(cin, instr);
  //cin >> instr;
  char cur;
  int index = 0;
  int input;
  int counter;
  for(int i = 0; i < instr.length(); ++i){
    //debug info
    /*
    cout << "i: " << i << endl;
    for(int j = 0; j < 10; j++){
      cout << data[j] << " ";
    }
    cout << endl;
    */
    cur = instr[i];
    //cout << cur << endl;

    if(cur == ';'){
      cout << "enter input: " << endl;
      cin >> input;
      data[index] = input;
    }
    else if(cur == ':'){
      cout << data[index] << endl;
    }

    else if(cur == '+'){
      data[index] = data[index] + 1;
    }
    else if(cur == '-'){
      data[index] = data[index] - 1;
    }

    else if(cur == '>'){
      index = index + 1;
    }
    else if(cur == '<'){
      index = index - 1;
    }

    else if(cur == '['){
      if(data[index] == 0){
        counter = 1;
        for(int j = i+1; j < instr.length(); ++j){
          if(instr[j] == '['){
            counter++;
          }
          else if(instr[j] == ']'){
            counter--;
            if(counter == 0){
              i = j;
              break;
            }
          }
        }
      }
    }
    else if(cur == ']'){
      if(data[index] != 0){
        counter = 1;
        for(int j = i-1; j >= 0; --j){
          if(instr[j] == ']'){
            counter++;
          }
          else if(instr[j] == '['){
            counter--;
            if(counter == 0){
              i = j;
              break;
            }
          }
        }
      }
    }
 
    else if(cur == '?'){
      cout << "instruction: " << cur << " (" << i << ")" << endl;
      cout << "index: " << index << endl;
      for(int j = 0; j < 10; j++){
        cout << data[j] << " ";
      }
      cout << endl;
    }
  }
  cout << "finished" << endl;
}
/*


loop, input, copy space, output



> ; input 0 5 0 0 (on 2)
[ - < + > > + < ] copy to temp squares 5 0 5 0 (on 2)
> shift right 5 0 5 0 (on 3)
[ - < + > ] copy to input square 5 5 0 0 (on 3)
< < shift left 5 5 0 0 (on 1)
[ - > [ - > + > + < < ] > [ - < + > ] < - < ] 0 0 0 15 (on 1)
> > > 0 0 0 15 (on 4)
:


BF code:
>;[-<+>>+<]>[-<+>]<<[->[->+>+<<]>[-<+>]<-<]>>>:

*/









