#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cstdlib> //rand()
#include <map> //unordered_map included?
#include <algorithm>
#include <memory>
#include <set>
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

string input_player(){
    string guess;
    cin >> guess;
    return guess;
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
class Player { //base class
public:
    virtual ~Player(){}
    virtual string get_guess() = 0;
    virtual void give_clue(pair<int,int> clue) = 0;
};

// int game(int digits, Player *player)
int game(int digits, Player *player){ //REWRITE GAME
    string num = genNum(digits);
    //num = "850";
    pair<int, int> picofermi = {0, 0};
  
    int turns = 0;
  
    while(picofermi != make_pair(0, digits)) {
        string guess = player->get_guess();
        cout << "your guess was: " << guess << endl;
        picofermi = clue(num, guess);
        cout << "your clue was: " << picofermi.first << ", " << picofermi.second << endl;
        player->give_clue(picofermi);
        turns += 1;
    }
    cout << "turns: " << turns << endl;
    return turns;
}
  

class RealPlayer : public Player { //FOR ALL SUB CLASSES ADD OVERRIDE DESTRUCTOR
public:
    ~RealPlayer() override {} //destructor
    
    string get_guess() override {
        return input_player();
    }
    void give_clue(pair<int,int> clue) override {
        cout << writeClue(clue) << endl;
    }
};

class PlayerAiRandom : public Player {
private:
    int digits;
    pair<int, int> clue;
    
public:
    ~PlayerAiRandom() override {} //destructor
    
    PlayerAiRandom(int new_digits){ //constructor
        digits = new_digits;
    }
    // PlayerAiRandom(int new_digits) : digits(new_digits) {}
    
    string get_guess() override { //random guesses with potential repeats
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
    void give_clue(pair<int, int> new_clue) override { //function to take input of clue
        clue = new_clue; //other than this do absolutely n o t h i n g
    }
};

class PlayerAiRandom2 : public Player{
private:
    int digits;
    pair<int, int> clue;
    
    vector<string> pos_guesses;
    
    vector<string> pos_guess_comb2(string cur_str, string available_digits){
        if(cur_str.size() == digits){
            return {cur_str};
        }
        vector<string> ans;
        for(int i = 0; i < available_digits.size(); ++i){
            string temp_available_digits = available_digits;
            temp_available_digits.erase(temp_available_digits.begin() + i);
            for(const auto &elem: pos_guess_comb2(cur_str + available_digits[i], temp_available_digits)){
                ans.push_back(elem);
            }
        }
        return ans;
    }
public:
    ~PlayerAiRandom2() override {} //destructor
    
    PlayerAiRandom2(int new_digits){
        digits = new_digits;
        
        pos_guesses = pos_guess_comb2("", "0123456789");
    }
    string get_guess() override{
        int index = rand()%(pos_guesses.size()); //maybe replace this with self made random function
        
        string ans = pos_guesses[index];
        pos_guesses.erase(pos_guesses.begin() + index);
        
        return ans;
    }
    void give_clue(pair<int, int> new_clue) override {
        clue = new_clue;
    }
};

class PlayerAiEliminate : public Player {
private:
    int digits;
    pair<int, int> clue;
    string last_guess;
    
    vector<string> pos_guesses;
    
    vector<vector<int>> gen_fermi(vector<int> cur_set, int index, int fermi_num){
        if(cur_set.size() == fermi_num){ //max digits
            return {cur_set};
        }
        if(index == digits){ //no more digits
            return {};
        }
        vector<vector<int>> ans;
        for(const auto &elem: gen_fermi(cur_set, index + 1, fermi_num)){ //choice to not include
            if(elem.size() != 0){
                ans.push_back(elem);
            }
        }
        cur_set.push_back(index);
        for(const auto &elem: gen_fermi(cur_set, index + 1, fermi_num)){ //choice to include
            if(elem.size() != 0){
                ans.push_back(elem);
            }
        }
        return ans; //vector of both choices
    }
    
    vector<vector<int>> gen_pico(vector<int> cur_set, vector<int> remaining_digits, int pico_num){ //I think I can reduce space by passing remaining_digits as a reference and pass in an additional index int
        if(cur_set.size() == pico_num){
            return {cur_set};
        }
        if(remaining_digits.size() == 0){
            return {};
        }
        vector<vector<int>> ans;
        int cur_digit = remaining_digits.front();
        remaining_digits.erase(remaining_digits.begin());
        for(const auto &elem: gen_pico(cur_set, remaining_digits, pico_num)){
            if(elem.size() != 0){
                ans.push_back(elem);
            }
        }
        cur_set.push_back(cur_digit);
        for(const auto &elem: gen_pico(cur_set, remaining_digits, pico_num)){
            if(elem.size() != 0){
                ans.push_back(elem);
            }
        }
        return ans;
    }
    //replaced with pico_permutations2
    vector<vector<int>> pico_permutations(vector<int> cur_set, vector<int> &original, int index, vector<bool> visited){
        if(cur_set.size() == original.size()){
            return {cur_set};
        }
        vector<vector<int>> ans;
        for(int i = 0; i < original.size(); ++i){
            if((i == index || visited[i]) && original.size() != 1){ //no digits can be in the same location (because it's pico); digits may not be repeated
                continue;
            }
            vector<int> temp_cur_set = cur_set;
            temp_cur_set.push_back(original[i]);
            
            vector<bool> temp_visited = visited;
            temp_visited[i] = true;
            for(const auto &elem: pico_permutations(temp_cur_set, original, index + 1, temp_visited)){
                ans.push_back(elem);
            }
        }
        return ans;
    }
    vector<vector<int>> pico_permutations2(vector<int> cur_set, vector<int> cur_pico, vector<int> available_digits, int pico_size){
        
        //for each digit get a different digit
        if(cur_set.size() == pico_size){ //filled all the digits
            return {cur_set};
        }
        vector<vector<int>> ans;
        for(int i = 0; i < available_digits.size(); ++i){
            if(available_digits[i] == cur_pico.front()){
                continue;
            }
            vector<int> temp_cur_set = cur_set;
            temp_cur_set.push_back(available_digits[i]);
            
            vector<int> temp_cur_pico = cur_pico;
            temp_cur_pico.erase(temp_cur_pico.begin());
            
            vector<int> temp_available_digits = available_digits;
            temp_available_digits.erase(temp_available_digits.begin() + i);
            
            for(const auto &elem: pico_permutations2(temp_cur_set, temp_cur_pico, temp_available_digits, pico_size)){
                if(elem.size() != 0){
                    ans.push_back(elem);
                }
            }
        }
        return ans;
    }
    bool compare_guesses(string ans_guess, string fut_guess){
        for(int i = 0; i < ans_guess.size(); ++i){
            if(ans_guess[i] == 'x'){ //there cannot be any duplicates
                for(const auto &elem: last_guess){
                    if(fut_guess[i] == elem){
                        return false;
                    }
                }
            }
            else if(ans_guess[i] != fut_guess[i]){
                return false;
            }
        }
        return true;
    }
    vector<string> pos_guess_comb2(string cur_str, string available_digits){ //shorter method than pos_guess_comb(1)
        if(cur_str.size() == digits){
            return {cur_str};
        }
        vector<string> ans;
        for(int i = 0; i < available_digits.size(); ++i){
            string temp_available_digits = available_digits;
            temp_available_digits.erase(temp_available_digits.begin() + i);
            for(const auto &elem: pos_guess_comb2(cur_str + available_digits[i], temp_available_digits)){
                ans.push_back(elem);
            }
        }
        return ans;
    }
    
    vector<string> pos_guess_comb(string cur_str, int index){
        if(cur_str.length() == digits){
            return {cur_str};
        }
        if(index > 9){
            return {};
        }
        vector<string> ans;
        for(const auto &elem: pos_guess_comb(cur_str, index + 1)){
            ans.push_back(elem);
        }
        char cur_char = '0' + index;
        for(const auto &elem: pos_guess_comb(cur_str + cur_char, index + 1)){
            ans.push_back(elem);
        }
        return ans;
    }
    
    vector<string> all_perms(string cur_str){
        vector<string> ans;
        while(next_permutation(cur_str.begin(), cur_str.end())){
            ans.push_back(cur_str);
        }
        return ans;
    }
    
    void init_pos_guesses(){
        /*
        pos_guesses = pos_guess_comb("", 0); //generate all combinations
        int pre_size = pos_guesses.size();
        for(int i = 0; i < pre_size; ++i){
            for(const auto &elem: all_perms(pos_guesses[i])){
                pos_guesses.push_back(elem);
            }
        }
        */
        pos_guesses = pos_guess_comb2("", "0123456789");
    }
public:
    ~PlayerAiEliminate() override {} //destructor
    
    
    PlayerAiEliminate(int new_digits){ //constructor
        digits = new_digits;
        
        init_pos_guesses();
        
        /*
        cout << "pos_guesses: " << endl;
        for(const auto &elem: pos_guesses){
            cout << elem << endl;
        }
        cout << endl;
        */
    }
    
    string get_guess() override { //random guesses with potential repeats (I'm guessing a better implementation for the guessing function would be to not guess a RANDOM one...)
        string ans = pos_guesses[rand()%pos_guesses.size()];
        last_guess = ans;
        return ans;
    }
    void give_clue(pair<int, int> new_clue) override { //function to take input of clue THERE ARE LIKE 4 NESTED LOOPS IN THIS (WITH RECURSION IN THE MIDDLE)
        clue = new_clue;
        
        vector<string> pos_ans; //I generate all possible answers from the clue and my guess and then intersect pos_ans and pos_guesses (there's probably a faster way to eliminate invalid guesses... but I couldn't figure out a clean solution to check if a guess matches my last guess)
        //First I tried to iterate through my possible guesses and determine if they would yield a different clue
        //And then I tried to "use logic" to remove some guesses but that algorithm got confusing and over-complicated quick
        //So I just landed on finding all possible answers :|
        
        vector<vector<int>> fermi_vec = gen_fermi({}, 0, new_clue.second);
        if(fermi_vec.size() == 0){ //so it has at least 1 iteration
            fermi_vec.push_back({});
        }
        /*
        cout << "fermi_vec: " << endl;
        for(const auto &elem: fermi_vec){
            for(const auto &elem2: elem){
                cout << elem2;
            }
            cout << endl;
        }
        cout << endl;
        */
        
        for(auto &fermi_comb: gen_fermi({}, 0, new_clue.second)){ //iterate through possible fermi combinations (Is creating fermi and pico combinations doable in 1 "recursion loop"?)
            //generate possible pico combinations
            //get list of possible pico digits based on elem
            vector<bool> used_digits(digits, false);
            for(const auto &cur_digit: fermi_comb){
                used_digits[cur_digit] = true;
            }
            vector<int> remaining_digits;
            for(int i = 0; i < used_digits.size(); ++i){
                if(!used_digits[i]){
                    remaining_digits.push_back(i);
                }
            }
            /*
            cout << "remaining_digits: " << endl;
            for(const auto &elem: remaining_digits){
                cout << elem << endl;
            }
            cout << endl;
            */
            vector<vector<int>> pos_picos = gen_pico({}, remaining_digits, new_clue.first);
            if(pos_picos.size() == 0){ //so it has at least 1 iteration
                pos_picos.push_back({});
            }
            /*
            cout << "pos_picos: " << endl;
            for(const auto &elem: pos_picos){
                for(const auto &elem2: elem){
                    cout << elem2;
                }
                cout << endl;
            }
            cout << endl;
            */
            for(auto &pico_comb: pos_picos){
                vector<int> available_digits;
                for(int i = 0; i < digits; ++i){
                    available_digits.push_back(i);
                }
                vector<vector<int>> pico_perms = pico_permutations2({}, pico_comb, available_digits, pico_comb.size()); //every valid permutation for each pico combination
                if(pico_perms.size() == 0){
                    pico_perms.push_back({});
                }
                /*
                cout << "pico_perms: " << endl;
                for(const auto &elem: pico_perms){
                    for(const auto &elem2: elem){
                        cout << elem2;
                    }
                    cout << endl;
                }
                */
                for(auto &cur_pico_perm: pico_perms){
                    string cur_ans(digits, 'x'); //x is so I know there is no digit for that space yet
                    for(auto &fermi_digit: fermi_comb){
                        char cur_char = last_guess[fermi_digit];
                        cur_ans[fermi_digit] = cur_char;
                    }
                    /*
                    for(auto &pico_digit: cur_pico_perm){
                        char cur_char = last_guess[pico_digit];
                        cur_ans[pico_digit] = cur_char;
                    }
                     */
                    for(int i = 0; i < cur_pico_perm.size(); ++i){
                        char cur_char = last_guess[cur_pico_perm[i]];
                        cur_ans[pico_comb[i]] = cur_char;
                    }
                    //done creating 1 possible answer
                    pos_ans.push_back(cur_ans);
                }
            }
        }
        //I have a vector of possible answers
        //take intersection of pos_ans with pos_guesses
        //Sorting the two vectors and using set_intersection will result in O(n) (I think), but I need to compare certain digits (I don't want to create another recursive function to fill in all the unfilled digits -- I'm guessing that takes more time)
        //Soooo guess I'll just use O(n^2) and check every one
        /*
        cout << "pos_ans: " << endl;
        for(const auto &elem: pos_ans){
            cout << "   " << elem << endl;
        }
        cout << endl;
        */
        
        vector<string> ans;
        
        for(const auto &elem: pos_guesses){
            bool valid = false;
            for(const auto &elem2: pos_ans){
                if(compare_guesses(elem2, elem)){
                    valid = true;
                    //cout << "VALID IS TRUE" << endl;
                }
            }
            if(valid){
                ans.push_back(elem);
            }
            else{
                //cout << elem << " is not valid" << endl;
            }
        }
        
        cout << "DIFFERENCE: " << pos_guesses.size() - ans.size() << endl;
        
        pos_guesses = ans;
        
        cout << "pos_guesses: " << endl;
        for(const auto &elem: pos_guesses){
            cout << elem << endl;
        }
        cout << endl;
    }
};



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
        clue = new_clue;

    }
};

// 1. Fix the random-without-repeats AI so that it runs in the new refactor
// 2. Make a copy of this, "random with elimination", that rules out possibilities
// based on the pfb answer, when give_clue() is called.

/*
enum Possibility_e{ //Just wanted to experiment with enums (instead of boolean states, in case I had to add more), allows me to name states instead of ints? idrk why I did this
    No, Pos, Prob, Used //No = no chance; Pos = possible, idk; Prob = clue gave fermi (guess from Probs if possible?), Used = used in previous digit (DO NOT CHOOSE)
};
enum Foo { Yes, No };

enum class Possibility_e { //requires explicit conversion to int; enum values are not global
    No, Pos, Prob, Used //No = no chance; Pos = possible, idk; Prob = clue gave fermi (guess from Probs if possible?), Used = used in previous digit (DO NOT CHOOSE)
};
Possibility_e::No

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
*/

bool compare_guesses2(string ans_guess, string fut_guess, string last_guess){
    for(int i = 0; i < ans_guess.size(); ++i){
        if(ans_guess[i] == 'x'){ //there cannot be any duplicates
            for(const auto &elem: last_guess){
                if(fut_guess[i] == elem){
                    return false;
                }
            }
        }
        else if(ans_guess[i] != fut_guess[i]){
            return false;
        }
    }
    return true;
}

int main(){
    cout << compare_guesses2("8x0", "850", "840") << endl;
    //cout << "oh yeah6" << endl;
    
    
    int digits;
    cout << "Enter the number of digits: " << endl;
    cin >> digits;

    string player_type;
    cout << "Enter the player type: " << endl;
    cin >> player_type;
    unique_ptr<Player> player;
    if (player_type == "random") {
        player.reset(new PlayerAiRandom(digits));
    }
    else if(player_type == "random2"){
        player.reset(new PlayerAiRandom2(digits));
    }
    else if(player_type == "elim"){
        player.reset(new PlayerAiEliminate(digits));
    }
    else {
        player.reset(new RealPlayer());
    }

    game(digits, player.get());
}

