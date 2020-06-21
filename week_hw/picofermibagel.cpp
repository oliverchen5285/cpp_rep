#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cstdlib> //rand()
using namespace std;

string genNum(const int &digits){ //no repeating digits
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




int main(){
  int digits;
  cout << "Enter the number of digits: " << endl;
  cin >> digits;

  game(digits, "player");
  
}
