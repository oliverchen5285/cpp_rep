#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cstdlib> //rand()
#include <map> //unordered_map included?
#include <algorithm>
using namespace std;

string genNum(const int digits){ //no repeating digits
  string ans = "";
  vector<int> nums = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int bound = 9;
  for(int i = 0; i < digits; ++i){
    int cur = rand()%(bound+1);
    ans += to_string(nums[cur]);
    swap(nums[cur], nums[bound]);
    bound -= 1;
  }
  return ans;
}

pair<int, int> clue(const string &num, const string &guess){ //keep in mind theres no repeating digits
  pair<int, int> picofermi = {0, 0}; //pico (first) = correct digit in incorrect place, fermi (second) = correct digit in correct place
  for(int i = 0; i < guess.length(); ++i){
    for(int j = 0; j < num.length(); ++j){
      if(guess[i] == num[j]){
        if(i == j){
          picofermi.second += 1;
        }
       else{
         picofermi.first += 1;
       }
      }
    }
  }
  return picofermi;
}

string writeClue(const pair<int, int> &picofermi){ //maybe just not use
  cout << picofermi.first << ", " << picofermi.second << endl;
  if(picofermi.first == 0 && picofermi.second == 0){
    return "bagel";
  }
  string ans = "";
  for(int i = 0; i < picofermi.first; ++i){
    ans += "pico ";
  }
  for(int i = 0; i < picofermi.second; ++i){
    ans += "fermi ";
  }
  return ans;
}

string input_player(string &guess){
  cin >> guess;
  return guess;
}

int game(int digits, string mode){
  string num = genNum(digits);
  //string num = "730";
  pair<int, int> picofermi = {0, 0};

  int count = 0;

  while(picofermi != make_pair(0, digits)){
    string guess;
    cout << "Enter your guess: " << endl;
    if(mode == "player"){
      guess = input_player(guess);
    }
    else{
      guess = make_move()
    }
    picofermi = clue(num, guess);
    cout << "Pico = correct digit in incorrect place, fermi = correct digit in correct place" << endl;
    cout << writeClue(picofermi) << endl;
    count += 1;
  }
  
  cout << "Congratulations! You took " << count << " guess(es)!" << endl;
  return count;
}

/* previous class
class Comp{
private:
  int digits_num;
  struct Zone_S{
    vector<vector<int>> pos_vec; //vector of possibilities
    int pos_num; //number of digits in zone
  };
  vector<Zone_S> zones_vec; //vector of zones (starts out as 1 big zone)
  int total_zones_num = 0;
  bool zones_created = false; //boolean representing if all digits have been split into zones

  vector<int> guess;
  
  void split_zones(){ //helper function to split last (biggest) zone into 2
    Zone_S last_zone = zones_vec.back();
    zones_vec.pop_back();
    
    Zone_S zone1; //first zone (digits tall)
    zone1.pos_num = 0; //number of digits contained in zone not set yet
    for(int i = 0; i < digits_num; ++i){
      zone1.pos_vec.push_back(last_zone.pos_vec[i]); //push back digit vector
    }
    
    Zone_S zone2; //second zone (whatever is remaining)
    zone2.pos_num = last_zone.pos_num; //number of digits contained assume to contain sub-everything
    for(int i = digits_num; i < last_zone.pos_vec.size(); ++i){
      zone2.pos_vec.push_back(last_zone.pos_vec[i]);
    }
    
    zones_vec.push_back(zone1); zones_vec.push_back(zone2); //replace last_zone with 2 new zones
  }
  
  string guess_to_str(){
    str ans = "";
    for(const auto &elem: guess){
      ans += to_string(elem);
    }
    return ans;
  }
public:
  Comp(int new_digits_num){ //constructor
    digits_num = new_digits_num;
    
    Zone_S zone; //probably some 1 line way to do this
    for(int i = 0; i < 10; ++i){ //digits 0 - 9
      for(int j = 0; j < digits_num; ++j){ //going through each digit vector
        zone.pos_vec[i][j] = 1; //initializing all digits as possible (1)
      }
    }
    
    zone.pos_num = digits_num; //total number of digits in only zone (containing everything)
    zones_vec.push_back(zone);
  }
  
  string make_move(){ //EDIT: instead of actually splitting vector into zones, maybe create unordered_map with key pointing to digits_num amount of digits and value of pos_vec and pos_num
    if(!zones_created){ //not all zones are split yet
      //split zones_vec into zones
      split_zones(); //call split_zones
      
      //return answer
      guess.clear();
      int first_digit = digits_num * (zones_vec.size()-2);
      for(int i = 0; i < digits_num; ++i){
        guess.push_back(first_digit);
        first_digit += 1;
      }
      return guess_to_str();
    }
    else{ //all zones are split
      
    }
  }
  
  void get_clue(pair<int, int> clue){ //takes in pair of # of picos, # of fermis
    sort(guess.begin(), guess.end()); //sort digits in ascending order
    if(!zones_created){
      zones_vec[zones_vec.size()-2].pos_num = clue.first + clue.second; //number of digits in that zone
      zones_vec.back().pos_num -= zones_vec[i].pos_num; //remaining zone subtracted amount in split zone
      if(clue.second > 0){ //there is fermi
        for(int j = 0; j < digits_num; ++j){ //go through diagonal
          zones_vec[zones_vec.size()-2].pos_vec[j][j] = 2;
        }
      }
      else if(clue.first > 0){ //no fermi and yes pico
        for(int j = 0; j < digits_num; ++j){
          zones_vec[zones_vec.size()-2].pos_vec[j][j] = 0;
        }
      }
      if(zones_vec.back().pos_vec.size() <= digits_num){ //last remaining zone does not need to be split
        zones_created = true;
      }
    }
    else{ //zones already created
      
    }
  } //end of get_clue
  
  
};
 */

class Comp1_c{
private:
    int digits;
    pair<int, int> clue;
    
public:
    Comp1_c(int new_digits){ //constructor
        digits = new_digits;
    }
    
    string make_guess(){ //random guesses with potential repeats
        string ans = ""; //does the same thing as gen_num()
        vector<int> nums = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        int bound = 9;
        for(int i = 0; i < digits; ++i){
          int cur = rand()%(bound+1); //maybe create helper function to generate (moreso) (pseudo) random number in range (0, 9)
          ans += to_string(nums[cur]);
          swap(nums[cur], nums[bound]);
          bound -= 1;
        }
        return ans;
    }
    void get_clue(pair<int, int> new_clue){ //function to take input of clue
        clue = new_clue; //other than this do absolutely n o t h i n g
    }
}

class Comp2_c{
private:
    int digits;
    pair<int, int> clue;
    
    vector<string> pos_guesses;
    
public:
    Comp2_c(int new_digits){ //constructor
        digits = new_digits;
        
        //generate all possible guesses (once in constructor) -- I do this instead of repeatedly trying random guesses (until I get a different one) because iterating over everything once is probably better than every time...
        for(int i = 0; i < digits; ++i){ //iterate over every digit
            string temp_guess = "";
            for(int j = 0; j < 10; ++j){  //iterate over every possible digit value
                temp_guess += to_string(j);
            }
            pos_guesses.push_back(temp_guess);
        }
        //remove guesses with duplicate digits (invalid)
        for(int i = 0; i < pos_guesses.size(); ++i){
            vector<bool> vis_digits(10, false); //set all 10 digits to unvisited
            
            for(const auto &temp_digit: pos_guesses[i]){ //iterate through digits in every guess
                if(vis_digits[(int)temp_digit - '0']){ //if current digit already visited
                    pos_guesses.erase(pos_guesses.begin() + i); //erase current guess from vector
                    break;
                }
                vis_digits[(int)temp_digit - '0'] = true; //set current digit to visited
            }
        }
    }
    
    string make_guess(){ //random guesses without repeats
        int index = rand()%(pos_guesses.size()); //maybe replace this with self made random function
        
        string ans = pos_guesses[index];
        pos_guesses.erase(pos_guesses.begin() + index);
        
        return ans;
    }
    void get_clue(pair<int, int> new_clue){ //function to take input of clue
        clue = new_clue; //other than this do absolutely n o t h i n g
    }
}

enum Possibility_e{ //Just wanted to experiment with enums (instead of boolean states, in case I had to add more), allows me to name states instead of ints? idrk why I did this
    No, Pos, Prob, Used //No = no chance; Pos = possible, idk; Prob = clue gave fermi (guess from Probs if possible?), Used = used in previous digit (DO NOT CHOOSE)
};

class Comp3_c{
private:
    int digits;
    pair<int, int> clue;
    
    string guess;
    
    vector<pair<int, vector<Possibility_e>>> digit_probs;
    
    unordered_map<Possibility_e, int> pos_priority_map = {{No, 0}, {Pos, 1}, {Prob, 2}, {Used, 0}}; //made map just in case
    //in testing I'm pretty sure I could compare enum values with '>' but not add them with + (when I print them, they are represented as integers?)
    
    bool compare_digit_prob(pair<int, vector<Possibility_e>> x, pair<int, vector<Possibility_e>> y, int cur_digit){ //compares 2 elements of digit_probs by specific digit
        if(x.second[cur_digit] == y.second[cur_digit]){
            return x.first > y.first;
        }
        return pos_priority_map[x.second[cur_digit]] > pos_priority_map[y.second[cur_digit]]; //Maybe possible for all digits to be 0... (if previous digits chose all possible digits of current digit)
    }
    
    bool compare_digit_occur(pair<int, int> x, pair<int, int> y){ //helper function to sort pairs by second value used in sort_columns()
        return x.second > y.second; //maybe have to swap this?
    }
    
    vector<int> sort_columns(){ //returns vector based on which columns should be picked first (which ones have less options available...?)
        vector<pair<int, int>> ans;
        for(int i = 0; i < digits; ++i){
            ans.push_back({i, 0});
        }
        for(int i = 0; i < digit_probs.size(); ++i){ //iterate through every possible digit value
            for(int j = 0; j < digit_probs[i].second.size(); ++j){ //iterate through every digit
                ans[j] += min(1, pos_priority_map[digits_probs[i].second[j]]); //if adding anything, add 1 or 0
            }
        }
        sort(ans.begin(), ans.end(), compare_digit_occur);
    }
    
    
public:
    Comp3_c(int new_digits){ //constructor
        digits = new_digits;
        
        //maybe I can do this in initialization, but not sure about digits being passed in before digit_probs created?
        for(int i = 0; i < 10; ++i){ //iterate through every possible digit value
            vector<Possibility_e> temp_probs(digits, Pos); //initiate every digit's probability vec as filled with Pos (all possible)
            digit_probs.push_back({i, temp_probs}); //push back pair of digit value and vector
        }
    }
    
    string make_guess(){ //I still can't find a way to pick random numbers because picking the best numbers every time will likely get be stuck and picking different numbers every time won't really be using the clues
        string cur_guess = ""; //JUST ASSUME just ASSUME that this works SOMEOHOW
        
        
        for(int i = 0; i < digits; ++i){ //ok dang it dang it dang it -- after picking one element from one digit column, the other columns are affected and their order might change (and if I follow the initial order some columns may be empty)
            vector<int> digit_order = sort_solumns(); //does choosing the "best" set potentially result in infinite loop? (if best set never gives new limiting information) -- or "best" set never gives too much information because some digits give few info <- could make another enum value for "picked before in PREVIOUS guess"
            //sort each column to find best digit value
            //cur_guess +=
            //then I would have to temporarily update digit_probs so all of the digits that use the current one are marked as used
        }
        guess = cur_guess;
        return guess;
    }
    
    void get_clue(pair<int, int> new_clue){
        clue = new_clue;
        if(clue.second == digits){ //all fermi
            return;
        }
        if(clue.first == 0 && clue.second == 0){ //bagel
            for(const auto &cur_digit: guess){ //cur_digit is a char
                int cur_digit_int = (int)cur_digit - '0';
                fill(digit_probs[cur_digit_int].begin(), digit_probs[cur_digit_int].end(), '0');
            }
        }
        else if(clue.second > 0){ //if any of them are in the correct position
            for(int i = 0; i < guess.length(); ++i){ //cur_digit is a char
                int cur_digit_int = (int)guess[i] - '0';
                fill(digit_probs[cur_digit_int].second.begin(), digit_probs[cur_digit_int].second.end(), '1');
                digit_probs[cur_digit_int].second[i] == '2';
            }
        }
        else{
            for(int i = 0; i < guess.length(); ++i){ //cur_digit is a char
                int cur_digit_int = (int)guess[i] - '0';
                fill(digit_probs[cur_digit_int].second.begin(), digit_probs[cur_digit_int].second.end(), '0');
                digit_probs[cur_digit_int].second[i] == '1';
            }
        }
        
    }
    
}

int main(){
  int digits;
  cout << "Enter the number of digits: " << endl;
  cin >> digits;

  game(digits, "player");
  
}
