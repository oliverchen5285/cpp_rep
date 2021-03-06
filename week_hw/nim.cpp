//write an interactive nim game where computer is an option (1 pile of n stones, take [1, 2, 3] stones)
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <utility>
#include <map>
using namespace std;


int move(int stoneindex, int maxmoves){
  if(stoneindex == 0){
    return 0;
  }
  if(stoneindex <= maxmoves && stoneindex > 0){
    return stoneindex;
  }
  for(int i = 1; i <= maxmoves; ++i){
    if(move(stoneindex - i, maxmoves) == 0){
      return i;
    }
  }
  return 0;
}


int move2(int stoneindex, int maxmoves){
  vector<bool> winloss2(stoneindex + 1, false);
  winloss2[0] = false;
  for(int i = 1; i <= stoneindex; ++i){
    for(int j = 1; j <= maxmoves; ++j){
      if(i - j >= 0){
        if(winloss2[i - j] == false){
          winloss2[i] = true;
        }
      }
    }
  }
  /*
  for(int i = 0; i < winloss2.size(); ++i){
    if(winloss2[i] == false){
      cout << 0;
    }
    else{
      cout << 1;
    }
  }
  cout << endl;
  */
  if(winloss2[stoneindex] == true){
    for(int i = stoneindex; i >= stoneindex - maxmoves; --i){
      if(winloss2[i] == false){
        return stoneindex - i;
      }
    }
  }
  
  return 0;
  
}

bool play(int stonenum, int maxmoves){
  //returns true if player 1 wins, false if player 2 wins
  int mode;
  cout << "Double player(2), single player(1), computer v. computer(0)" << endl;
  cin >> mode;
  cout << "Stones remaining: " << stonenum << endl;
  while (true){
    int ans;
    if(mode == 2 || mode == 1){
      cout << "Player 1: "<< endl;
      cin >> ans;
    }
    else{
      ans = move2(stonenum, maxmoves);
    }
    stonenum -= ans;
    cout << "Player 1 took " << ans << endl;
    cout << "Stones remaining: " << stonenum << endl;
    if(stonenum <= 0){
      return true;
    }
    cout << endl;
    if(mode == 2){
      cout << "Player 2: " << endl;
      cin >> ans;
    }
    else{
      ans = move2(stonenum, maxmoves);
    }
    stonenum -= ans;
    cout << "Player 2 took " << ans << endl;
    cout << "Stones remaining: " << stonenum << endl;
    if(stonenum <= 0){
      return false;
    }
  }
}


int main(){
  cout << "move1" << endl;
  for(int i = 1; i < 11; ++i){
    cout << i << ": " << move(i, 3) << endl;
  }
  cout << endl << "move2" << endl;
  for(int i = 1; i < 11; ++i){
    cout << i << ": " << move2(i, 3) << endl;
  }
  if(play(10, 3)){
    cout << "Player 1 wins!" << endl;
  }
  else{
    cout << "Player 2 wins!" << endl;
  }
}

//function getstonesleft() returns how many stones, function makemove() returns take how many stones
//can be expanded to the true nim game (multiple piles, take any amount)

//play othello
