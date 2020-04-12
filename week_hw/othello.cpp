#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <utility>
#include <map>
using namespace std;

typedef pair<int, int> coord_t;
typedef pair<coord_t, int> coord_val_t;
typedef pair<bool, int[8][8]> mv_state_t;

void copyarr(int src[8][8], int tgt[8][8]){
  for(int i = 0; i < 8; ++i){
    for(int j = 0; j < 8; ++j){
      tgt[i][j] = src[i][i];
    }
  }
}

bool operator<(coord_val_t x, coord_val_t y){
  return x.second > y.second;
}


int weight[8][8] = {
  {7, 6, 5, 4, 4, 5, 6, 7},
  {6, 5, 4, 3, 3, 4, 5, 6},
  {5, 4, 3, 2, 2, 3, 4, 5},
  {4, 3, 2, 1, 1, 2, 3, 4},
  {4, 3, 2, 1, 1, 2, 3, 4},
  {5, 4, 3, 2, 2, 3, 4, 5},
  {6, 5, 4, 3, 3, 4, 5, 6},
  {7, 6, 5, 4, 4, 5, 6, 7}
};

int score(int board[8][8]){

  /*
  1 = self
  -1 = opponent
  0 = empty
  */

  int ans = 0;
  for(int i = 0; i < 8; ++i){
    for(int j = 0; j < 8; ++j){
      ans += weight[i][j] * board[i][j];
    }
  }
  return ans;
}

void possible(coord_t move, int board[8][8], mv_state_t ret_pair){
  cout << "in possible" << endl;
  bool ans = false;
  int ansboard[8][8];
  cout << "before copyarr" << endl;
  copyarr(board, ansboard);
  cout << "possible copy1" << endl;
  if(board[move.first][move.second] != 0){
    cout << "returning false" << endl;
    ret_pair.first = ans;
    copyarr(ansboard, ret_pair.second);
    cout << "returned false" << endl;
  }
  
  else {
    cout << "else" << endl;
    bool self = false;
    for(int i = move.first + 1; i < 8; ++i){
      if(board[i][move.second] == -1){
        cout << "found opp piece" << endl;
        self = true;
      }
      if(board[i][move.second] == 0){
        cout << "found blank square" << endl;
        break;
      }
      if(board[i][move.second] == 1){
        cout << "found self piece" << endl;
        if(self){
          cout << "valid answer" << endl;
          ans = true;
          for(int j = move.first; j <= i; ++j){
            ansboard[j][move.second] = 1;
          }
        }
        else{
          cout << "found self before opp piece" << endl;
          break;
        }
      }
    }
    cout << "possible 1" << endl;
    self = false;
    for(int i = move.first - 1; i >= 0; --i){
      if(board[i][move.second] == -1){
        self = true;
      }
      if(board[i][move.second] == 0){
        break;
      }
      if(board[i][move.second] == 1){
        if(self){
          ans = true;
          for(int j = move.first; j >= i; --j){
            ansboard[j][move.second] = 1;
          }
        }
        else{
          break;
        }
      }
    }
    
    cout << "possible 2" << endl;
    self = false;
    for(int i = move.second + 1; i < 8; ++i){
      if(board[move.first][i] == -1){
        self = true;
      }
      if(board[move.first][i] == 0){
        break;
      }
      if(board[move.first][i] == 1){
        if(self){
          ans = true;
          for(int j = move.second; j <= i; ++j){
            ansboard[move.first][j] = 1;
          }
        }
        else{
          break;
        }
      }
    }
    
    cout << "possible 3" << endl;
    self = false;
    for(int i = move.second - 1; i >= 0; ++i){
      if(board[move.first][i] == -1){
        self = true;
      }
      if(board[move.first][i] == 0){
        break;
      }
      if(board[move.first][i] == 1){
        if(self){
          ans = true;
          for(int j = move.second; j >= i; --j){
            ansboard[move.first][j] = 1;
          }
        }
        else{
          break;
        }
      }
    }
    
    cout << "possible 4" << endl;
    self = false;
    for(int i = 1; i+move.first < 8 && i+move.second < 8; ++i){
      if(board[move.first + i][move.second + i] == -1){
        self = true;
      }
      if(board[move.first + i][move.second + i] == 0){
        break;
      }
      if(board[move.first + i][move.second + i] == 1){
        if(self){
          ans = true;
          for(int j = 0; j <= i; ++j){
            ansboard[move.first + j][move.second + j] = 1;
          }
        }
        else{
          break;
        }
      }
    }
    
    cout << "possible 5" << endl;
    self = false;
    for(int i = 1; move.first-i >= 0 && move.second-i >= 0; ++i){
      if(board[move.first - i][move.second - i] == -1){
        self = true;
      }
      if(board[move.first - i][move.second - i] == 0){
        break;
      }
      if(board[move.first - i][move.second - i] == 1){
        if(self){
          ans = true;
          for(int j = 0; j <= i; ++j){
            ansboard[move.first - j][move.second - j] = 1;
          }
        }
        else{
          break;
        }
      }
    }
    
   
    cout << "possible 6" << endl;
    self = false;
    for(int i = 1; move.first+i < 8 && move.second-i >= 0; ++i){
      if(board[move.first + i][move.second - i] == -1){
        self = true;
      }
      if(board[move.first + i][move.second - i] == 0){
        break;
      }
      if(board[move.first + i][move.second - i] == 1){
        if(self){
          ans = true;
          for(int j = 0; j <= i; ++j){
            ansboard[move.first + j][move.second - j] = 1;
          }
        }
        else{
          break;
        }
      }
    }
    
    
    cout << "possible 7" << endl;
    self = false;
    for(int i = 1; move.first-i >= 0 && move.second+i < 8; ++i){
      if(board[move.first - i][move.second + i] == -1){
        self = true;
      }
      if(board[move.first - i][move.second + i] == 0){
        break;
      }
      if(board[move.first - i][move.second + i] == 1){
        if(self){
          ans = true;
          for(int j = 0; j <= i; ++j){
            ansboard[move.first - j][move.second +j] = 1;
          }
        }
        else{
          break;
        }
      }
    }
    
    cout << "possible 8" << endl;
    ret_pair.first = ans;
    copyarr(ansboard, ret_pair.second);
    cout << "end of possible" << endl;
    if(ret_pair.first){
      cout << "possible return true" << endl;
    }
  }
}

void  reverseboard(int board[8][8], int newboard[8][8]){
  copyarr(board, newboard);
  for(int i = 0; i < 8; ++i){
    for(int j = 0; j < 8; ++j){
      newboard[i][j] *= -1;
    }
  }
}

coord_val_t makemove(int board[8][8], int depth){ 
  priority_queue<coord_val_t> posmoves;
  //((x, y), score)
  for(int i = 0; i < 8; ++i){
    for(int j = 0; j < 8; ++j){
      //get possible moves
      mv_state_t temp;
      possible(make_pair(i,j), board, temp);
      if(temp.first){
        cout << "adding possible move" << endl;
        posmoves.push(make_pair(make_pair(i, j), score(temp.second)));
      }
    }
  }
  cout << "makemove reach" << endl;
  if(depth == 3){
    cout << "makemove depth reached:" << endl;
    return make_pair(make_pair(posmoves.top().first.first, posmoves.top().first.second), (posmoves.top().second));
  }
  coord_val_t bestmove = make_pair(make_pair(-1, -1), 0);
  cout << "makemove reach" << endl;
  if(posmoves.empty()){
    cout << "posmoves is empty" << endl;
  }
  while(!posmoves.empty()){
    cout << "makemove while loop" << endl;
    /*
    change 1 to -1, -1 to 1
    makemove(reversed board, depth + 1)
    makemove(reversed reversed board, depth + 1)
    */
    mv_state_t temp;
    int curboard[8][8];
    possible(posmoves.top().first, board, temp);
    copyarr(temp.second, curboard);
    
    int oppboard[8][8];
    
    reverseboard(curboard, oppboard);
    coord_t oppmove = makemove(oppboard, depth + 1).first;
    
    int newboard[8][8];
    possible(oppmove, oppboard, temp);    
    reverseboard(temp.second, newboard);    
        
    coord_val_t newans = makemove(newboard, depth + 1);
    if(newans.second > bestmove.second){
      bestmove.second = newans.second;
      bestmove.first = newans.first;
    }
    
  }
  cout << "makemove end of while" << endl;  
  return bestmove; 
}

void printboard(int board[8][8]){
  for(int i = 0; i < 8; ++i){
    for(int j = 0; j < 8; ++j){
      if(board[i][j] == -1){
        cout << "x ";
      }
      else if(board[i][j] == 1){
        cout << "o ";
      }
      else{
        cout << ". ";
      }
    }
    cout << endl;
  }
  cout << endl;
}

void play(){
  int start[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, -1, 1, 0, 0, 0},
    {0, 0, 0, 1, -1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
  };
  while(true){
    printboard(start);

    coord_t move1 = makemove(start, 0).first;
    cout << "debug: reach 1" << endl;
    if(move1.first == -1){
      cout << "2 wins!" << endl;
      break;
    }
    mv_state_t temp;
    possible(move1, start, temp);
    copyarr(temp.second, start);
    
    cout << "debug: reach 2" << endl;
    printboard(start);
    
    coord_t move2 = makemove(start, 0).first;
  
    cout << "debug: reach 3" << endl;

    if(move2.first == -1){
      cout << "1 wins!" << endl;
      break;
    }

    possible(move2, start, temp);
    copyarr(temp.second, start);
    
    cout << "debug: reach 4" << endl;
  }
}

int main(){
  play();
}
