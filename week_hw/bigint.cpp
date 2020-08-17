#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Bignat{
private:
  string num;
  
  void remove_zeros(string &n){
    for(int i = 0; i < n.length() - 1; ++i){
      if(n[i] == '0'){
        n.erase(n.begin() + i);
        --i;
      }
      else{
        break;
      }
    }
    return;
  }
public:
  Bignat() : num(0)
  {}
  Bignat(const string new_str) : num(new_str)
  {}
  Bignat(const int new_int) : num(to_string(new_int))
  {}
  string get_num(){
    return num;
  }
  Bignat operator + (Bignat &bg){
    string n1 = num;
    string n2 = bg.get_num();
    string ans = "";
    reverse(n1.begin(), n1.end());
    reverse(n2.begin(), n2.end());
    
    int carry = 0;
    for(int i = 0; i < max(n1.length(), n2.length()) + 1; ++i){ //max len + 1 for extra carry (gain 1 digit)
      int digit = 0;
      digit += (i < n1.length())? n1[i] - '0': 0;
      digit += (i < n2.length())? n2[i] - '0': 0;
      digit += carry;
      
      carry = digit/10;
      digit %= 10;
      ans += digit + '0';
    }
    
    reverse(ans.begin(), ans.end());
    remove_zeros(ans);
    return Bignat(ans);
  }
  bool operator < (Bignat &bg){
    return num.length() < bg.get_num().length() || (num.length() == bg.get_num().length() && num < bg.get_num());
  }
  bool operator > (Bignat &bg){
    return num.length() > bg.get_num().length() || (num.length() == bg.get_num().length() && num > bg.get_num());
  }
  bool operator == (Bignat &bg){
    return num == bg.get_num();
  }
  bool operator <= (Bignat &bg){
    return Bignat(num) < bg || Bignat(num) == bg;
  }
  bool operator >= (Bignat &bg){
    return Bignat(num) > bg || Bignat(num) == bg;
  }
  Bignat operator - (Bignat &bg){
    string n1 = max(num, bg.get_num());
    string n2 = min(num, bg.get_num());
    reverse(n1.begin(), n1.end());
    reverse(n2.begin(), n2.end());
    string ans = "";     
     
    for(int i = 0; i < n1.length(); ++i){ //n1 guaranteed longer
      int borrow = ((n1[i] == 'a')? -1 : n1[i] - '0') - ((i < n2.length()) ? n2[i] - '0' : 0);
      int digit = (borrow >= 0)? borrow : borrow + 10;
      n1[i + 1] = (borrow >= 0)? n1[i + 1] : (n1[i+1] - '0' > 0) ? (n1[i + 1] - '0') - 1 + '0' : 'a';
      ans += digit + '0';
    }
    reverse(ans.begin(), ans.end());   
    remove_zeros(ans);
    return Bignat(ans);
  }
  Bignat operator * (Bignat &bg){
    string n1 = num;
    string n2 = bg.get_num();
    reverse(n1.begin(), n1.end());
    reverse(n2.begin(), n2.end());
    
    string ans = "";
    
    for(int i = 0; i < n1.length(); ++i){
      string digit_ans = "";
      int carry = 0;
      for(int j = 0; j < n2.length() + 1; ++j){ //extra carry (gain 1 digit)
        int digit = (n1[i] - '0') * (j < n2.length()? n2[j] - '0' : 0) + carry;
        //cout << digit << endl;
        carry = digit / 10;
        digit %= 10;
        
        digit_ans += digit + '0';
      }
      reverse(digit_ans.begin(), digit_ans.end());
      remove_zeros(digit_ans);
      for(int j = 0; j < i; ++j){
        digit_ans += "0";
      }
      //cout << "digit_ans: " << digit_ans << endl;
      //cout << n1[i] << " * " << bg.get_num() << " = " << digit_ans << endl;
      Bignat a(digit_ans);
      Bignat b(ans);
      ans = (a + b).get_num();
      //cout << "ans: " << ans << endl;
      //ans = (Bignat(digit_ans) + Bignat(ans)).get_num();
    }
    return Bignat(ans);
  }
  
  Bignat operator / (Bignat &bg){
    string n2 = num;
    string n1 = bg.get_num();
    string ans = "0";
  
    for(int i = n1.length(); i <= n2.length(); ++i){
      string cur_n = n2.substr(0, i);
      cout << "n2: " << n2 << endl;
      cout << "cur_n: " << cur_n << endl;
      int digit = 0;
      for(int j = 9; j >= 0; --j){ 
        Bignat big_cur_n(cur_n);
        Bignat big_n1(n1);
        Bignat big_j(j);
        Bignat big_prod = big_n1 * big_j;
        //cout << "big_prod: " << big_prod.get_num() << endl;
        //cout << "reached 2" << endl;
        Bignat big_zero(0);
        //cout << "reached 3" << endl;
        if(big_prod <= big_cur_n){
          cout << big_n1.get_num() << "*" << big_j.get_num() << " = " << big_prod.get_num() << endl;
          cout << big_prod.get_num() << " <= " << big_cur_n.get_num() << endl;
          digit = j;
          int prev_size = n2.length();
          //cout << "reached 1" << endl;
          n2.erase(n2.begin(), n2.begin() + i);
          //cout << "reached" << endl;
          string div = (big_cur_n - big_prod).get_num();
          cout << "div: " << div << endl;
          n2.insert(0, (div != "0")? div : "");
          i -= prev_size - n2.length();
          break;
        }
      }
      cout << cur_n << " / " << n1 << " = " << digit << endl;
      ans += digit + '0';
    }
    remove_zeros(ans);
    return Bignat(ans);
  }
  
};

int main(){
  Bignat a("842843");
  Bignat b(235);
  //cout << (a + b).get_num() << endl;
  //cout << (b - a).get_num() << endl;
  //cout << (a * b).get_num() << endl;
  cout << (a / b).get_num() << endl;
}
