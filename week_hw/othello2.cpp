#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <utility>
#include <map>
using namespace std;

//type aliases end in "_t", structs end in "_s"
//"_t" indicates stl stuff, "_s" indicates ya know self-made structs
//I guess "_c" will indicate classes idk

using board_t = vector<vector<int> >;
using move_t = pair<int, int>;
using dir_t = pair<int, int>;

//used in make_move() in vector pos_move_board_scores for sorting structs as opposed to sorting three vectors based on one
struct move_board_score_s{
  move_t move;
  board_t board;
  int score;
};

//used as return value of make_move() to provide move_t (answer) and int score to compare future moves
struct move_score_s{
  move_t move;
  int score;
};

//board_t of weights to create score for different board states
board_t weight = {
 {7, 6, 5, 4, 4, 5, 6, 7},
 {6, 5, 4, 3, 3, 4, 5, 6},
 {5, 4, 3, 2, 2, 3, 4, 5},
 {4, 3, 2, 1, 1, 2, 3, 4},
 {4, 3, 2, 1, 1, 2, 3, 4},
 {5, 4, 3, 2, 2, 3, 4, 5},
 {6, 5, 4, 3, 3, 4, 5, 6},
 {7, 6, 5, 4, 4, 5, 6, 7} };

//returns int representing score of board, given board_t representing board state
//should add winning and losing boards (return greatest score for board that has won and return lowest score for board that has lost)
int make_score(const board_t cur_board){
  //cout << "enter make_score()" << endl;
  int score = 0;
  for(int i = 0; i < 8; ++i){
    for(int j = 0; j < 8; ++j){
      score += weight[i][j] * cur_board[i][j];
    }
  }
  //cout << "exit make_score()" << endl;
  return score;
}

//returns bool representing if ray yields possible move, given board_t representing current board state, move representing current move, and dir representing direction of ray
bool ray(board_t cur_board, move_t cur_move, dir_t cur_dir){
  //cout << "enter ray()" << endl;
  //debug print statement for direction clarification
  //cout << cur_dir.first << ", " << cur_dir.second << " = ";
  if(cur_dir.second == 1){
    //cout << "south ";
  }
  else if(cur_dir.second == -1){
    //cout << "north ";
  }
  
  if(cur_dir.first == 1){
    //cout << "east ";
  }
  else if(cur_dir.first == -1){
    //cout << "west ";
  }
  //cout << endl;
  bool hit_opp = false;
  for(int i = cur_move.first, j = cur_move.second; i < 8 && i >= 0 && j < 8 && j >= 0; i += cur_dir.first, j += cur_dir.second){
    //if move chosen is not on empty square, return false
    if(i == cur_move.first && j == cur_move.second && cur_board[i][j] != 0){
      //cout << "move not on empty square" << endl;
      //cout << "exit ray()" << endl;
      return false;
    }
    //if piece on ray belongs to opponent, set hit_opp to true
    if(cur_board[i][j] == -1){
      //cout << "hit opp" << endl;
      hit_opp = true;
    }
    //if non-first move is empty, return false
    if((i != cur_move.first || j != cur_move.second) && cur_board[i][j] == 0){
      //cout << "non-first move is empty" << endl;
      //cout << "exit ray()" << endl;
      return false;
    }
    //if hit piece belonging to self before hitting piece belonging to opponent, return false
    if(cur_board[i][j] == 1){
      if(!hit_opp){
        //cout << "hit piece belonging to self before hitting piece belonging to opponent" << endl;
        //cout << "exit ray()" << endl;
        return false;
      }
      else{
        //cout << "works" << endl;
        //cout << "exit ray()" << endl;
        return true;
      }
    }
  }
  //cout << "exit ray()" << endl;
  return false;  
}

vector<dir_t> dir_vec = {
 make_pair(1, 0), make_pair(-1, 0),
 make_pair(0, 1), make_pair(0, -1),
 make_pair(1, 1), make_pair(-1, -1),
 make_pair(-1, 1), make_pair(1, -1) };

//returns bool representing if move is possible, given board_t representing current board state, move representing current move
bool check_pos_move(board_t cur_board, move_t cur_move){
  //cout << "enter check_pos_move()" << endl;
  for(int i = 0; i < 8; ++i){
    if(ray(cur_board, cur_move, dir_vec[i])){
      //cout << "cur_move works" << endl;
      //cout << "exit check_pos_move()" << endl;
      return true;
    }
  }
  //cout << "exit check_pos_move()" << endl;
  return false;
}

//applies ray to board_t representing new board, given board_t representing new board, move_t representing current move, and dir_t representing current direction
void apply_ray(board_t &new_board, move_t cur_move, dir_t cur_dir){
  //cout << "enter apply_ray()" << endl;
  if(!ray(new_board, cur_move, cur_dir)){
    //cout << "exit apply_ray()" << endl;
    return;
  }
  //new_board[cur_move.first][cur_move.second] = 1;
  for(int i = cur_move.first + cur_dir.first, j = cur_move.second + cur_dir.second; 
   i >= 0 && i < 8 && j >= 0 && j < 8; i += cur_dir.first, j += cur_dir.second){
    if(new_board[i][j] == 1){
      break;
    }
    new_board[i][j] = 1;
  }
  //cout << "exit apply_ray()" << endl;
  return;
}

//returns board_t representing future board state, given board_t representing current board state and move_t representing current move
board_t apply_pos_move(board_t cur_board, move_t cur_move){
  //cout << "enter apply_pos_move" << endl;
  board_t new_board = cur_board;
  for(int i = 0; i < 8; ++i){
    apply_ray(new_board, cur_move, dir_vec[i]);
  }
  if(cur_move.first != -1 && cur_move.second != -1){
    new_board[cur_move.first][cur_move.second] = 1;
  }
  //cout << "exit apply_pos_move()" << endl;
  return new_board;
}

bool sort_move_board_score_des(move_board_score_s a, move_board_score_s b){
  //cout << "enter sort_move_board_score_des()" << endl;
  return a.score > b.score;
  //cout << "exit sort_move_board_score_des()" << endl;
}

board_t make_opp_board(board_t cur_board){
  //cout << "enter make_opp_board()" << endl;
  board_t opp_board = cur_board;
  for(auto &elem: opp_board){
    for(auto &elem2: elem){
      elem2 *= -1;
    }
  }
  //cout << "exit make_opp_board()" << endl;
  return opp_board;
}

//returns move representing optimal move (and maybe resulting score at depth 3), given board_t representing board state and int representing current recursion depth
move_score_s make_move(board_t cur_board, int depth){
  //cout << "enter make_move()" << endl;
  vector<move_board_score_s> pos_move_board_scores;
  for(int i = 0; i < 8; ++i){
    for(int j = 0; j < 8; ++j){
      move_t cur_move = make_pair(i, j);
      if(check_pos_move(cur_board, cur_move)){
        move_board_score_s temp_move_board_score;
        temp_move_board_score.move = cur_move;
        temp_move_board_score.board = apply_pos_move(cur_board, cur_move);
        temp_move_board_score.score = make_score(temp_move_board_score.board);

        pos_move_board_scores.push_back(temp_move_board_score);
      }
    }
  }
  //return score: -1, move: (-1, -1) if no possible moves exist
  if(pos_move_board_scores.empty()){
    move_score_s ret_move_score;
    ret_move_score.score = -1;
    ret_move_score.move = make_pair(-1, -1);

    //cout << "exit make_move()" << endl;
    return ret_move_score;
  }

  if(depth == 3){
    //sort vector of possible moves in descending order by score
    sort(pos_move_board_scores.begin(), pos_move_board_scores.end(), sort_move_board_score_des);
    move_score_s ret_move_score;
    ret_move_score.move = pos_move_board_scores.front().move;
    ret_move_score.score = pos_move_board_scores.front().score;
    //cout << "reached depth 3" << endl;
    //cout << "exit make_move()" << endl;
    return ret_move_score;
  }
  
  int best_score;
  move_t best_move;

  move_score_s cur_move_score;
  for(int i = 0; i < pos_move_board_scores.size(); ++i){
    board_t opp_board = make_opp_board(pos_move_board_scores[i].board);
    move_t opp_move = make_move(opp_board, depth + 1).move;
    opp_board = apply_pos_move(opp_board, opp_move);
    board_t fut_board = make_opp_board(opp_board); 
    
    cur_move_score = make_move(fut_board, depth+1);
    //if current move results in greater score than best_move does in best_score OR it is first iteration of for loop
    if(cur_move_score.score > best_score || i == 0){
      best_score = cur_move_score.score;
      best_move = pos_move_board_scores[i].move;
    }
    //pick move that results in board that generates greatest score
    //also check for winning boards
  }
  
  move_score_s ret_move_score;
  ret_move_score.score = best_score;
  ret_move_score.move = best_move;
  
  //cout << "exit make_move()" << endl;
  return ret_move_score;
}

void print_board(board_t cur_board){
  //cout << "enter print_board()" << endl;
  vector<char> jlist = {' ', '0', '1', '2', '3', '4', '5', '6', '7'};
  vector<char> ilist = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

  for(int i = 0; i < 9; ++i){
    cout << jlist[i] << " ";
  }
  cout << endl;
  for(int i = 0; i < 8; ++i){
    for(int j = 0; j < 9; ++j){
      if(j == 0){
        cout << ilist[i] << " ";
      }
      else{
        if(cur_board[i][j-1] == 0){
          cout << ". ";
        }
        else if(cur_board[i][j-1] == 1){
          cout << "o ";
        }
        else{
          cout << "x ";
        }
      }
    }
    cout << endl;
  }
  cout << endl;
  //cout << "exit print_board()" << endl;
}

void play(string mode){
  //cout << "enter play()" << endl;
  //(player vs. player == "pvp"), (player vs. computer == "pvc"), (computer vs. player == "cvp"), (computer vs. computer == "cvc")
  board_t play_board = {
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, -1, 1, 0, 0, 0},
   {0, 0, 0, 1, -1, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0} };
  
  unordered_map<char, int> i_move_map = { {'a', 0}, {'b', 1}, {'c', 2}, {'d', 3}, {'e', 4}, {'f', 5}, {'g', 6}, {'h', 7} };
  unordered_map<int, char> rev_i_move_map = { {0, 'a'}, {1, 'b'}, {2, 'c'}, {3, 'd'}, {4, 'e'}, {5, 'f'}, {6, 'g'}, {7, 'h'} };  

  move_t move1;
  move_t move2; 
  while(true){
    //player 1
    cout << endl;
    print_board(play_board);

    if(mode[0] == 'p'){
      bool move_pos = false;
      char i_move;
      int j_move;
      while(!move_pos){
        cout << "p1 enter move (character first, number second): " << endl;

        cin >> i_move >> j_move;
      
        move1.first = i_move_map[i_move];
        move1.second = j_move;

        if(check_pos_move(play_board, move1)){
          move_pos = true;
        }
        else{
          cout << "invalid move" << endl;
        }
      }
    }

    else{
      move1 = make_move(play_board, 0).move;
    }
    cout << "p1 entered " << rev_i_move_map[move1.first] << ", " << move1.second << endl;
    
    //create function to determine who won
    if(move1.first == -1 && move1.second == -1){
      cout << "game end" << endl;
      break;
    }
    play_board = apply_pos_move(play_board, move1);
    
    cout << endl;
    print_board(play_board);
    
    play_board = make_opp_board(play_board);
    
    cout << endl;
    print_board(play_board);
    
    if(mode[2] == 'p'){
      bool move_pos = false;
      char i_move;
      int j_move;
      while(!move_pos){
        cout << "p2 enter move (character first, number second): " << endl;

        cin >> i_move >> j_move;
  
        move2.first = i_move_map[i_move];
        move2.second = j_move;

        if(check_pos_move(play_board, move2)){
          move_pos = true;
        }
        else{
          cout << "invalid move" << endl;
        }
      }
    }
    else{
      move2 = make_move(play_board, 0).move;
    }
    cout << "p2 entered " << rev_i_move_map[move2.first] << ", " << move2.second << endl;
 

    if(move2.first == -1 && move2.second == -1){
      cout << "game end" << endl;
      break;
    }
    play_board = apply_pos_move(play_board, move2);

    cout << endl;
    print_board(play_board);

    play_board = make_opp_board(play_board);
  }
  //cout << "exit play()" << endl;
}

int main(){
  string mode;
  cout << "Enter mode (pvp, cvp, pvc, cvc): " << endl;
  cin >> mode;
  play(mode); 
}


