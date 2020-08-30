#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
using namespace std;
class Bignat{
private:
  string num;

  int int_val(char digit){
    if(digit >= '0' && digit <= '9'){
        return digit - '0';
    }
    if(digit == 'z'){
        return -1;
    }
    return digit - 'a' + 10;
  }
  char char_val(int digit){
    if(digit >= 0 && digit <= 9){
        return digit + '0';
    }
    if(digit == -1){
        return 'z';
    }
    return digit -10 + 'a';
  }

  void remove_zeros(string &n){
    for(int i = n.size() -1; i >= 0; --i){
        if(n[i] == '0'){
            n.erase(n.begin() + i);
        }
        else{
            return;
        }
    }
  }
public:
  Bignat operator + (Bignat &bg){
    string n1 = num;
    string n2 = bg.get_num();
    string ans = "";
    //reverse(n1.begin(), n1.end());
    //reverse(n2.begin(), n2.end());
    
    int carry = 0;
    for(int i = 0; i < max(n1.length(), n2.length()) + 1; ++i){ //max len + 1 for extra carry (gain 1 digit)
      int digit = 0;
      digit += (i < n1.length())? int_val(n1[i]): 0;
      digit += (i < n2.length())? int_val(n2[i]): 0;
      digit += carry;
      
      carry = digit/32;
      digit %= 32;
      cout << "digit: " << digit << endl;
      ans += char_val(digit);
    }
    remove_zeros(ans);
    reverse(ans.begin(), ans.end());
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
    //reverse(n1.begin(), n1.end());
    //reverse(n2.begin(), n2.end());
    string ans = "";
     
    for(int i = 0; i < n1.length(); ++i){ //n1 guaranteed longer
      int digit = int_val(n1[i]) - (i < n2.length())? int_val(n2[i]): 0;
      if(digit < 0){
        digit += 32;
        n1[i+1] = char_val(int_val(n1[i+1]) - 1);
      }
      ans += char_val(digit);
    }
    remove_zeros(ans);
    reverse(ans.begin(), ans.end());
    
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
    cout << "reached" << endl;
    string n2 = num;
    string n1 = bg.get_num();
    string ans = "0";
  
    for(int i = n1.length(); i <= n2.length(); ++i){
      string cur_n = n2.substr(0, i);
      cout << "n2: " << n2 << endl;
      cout << "cur_n: " << cur_n << endl;
      int digit = 0;
      for(int j = 31; j >= 0; --j){
        cout << i << ", " << j << endl;
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
  Bignat operator %(Bignat &bg){
    Bignat num_big(num);
    Bignat quotient = num_big / bg;
    Bignat prod = quotient * bg;
    return num_big - prod;
  }
private:
  string base_10(string temp_num){ //base 32 to 10
    int ans = 0;
    int power = 32;
    for(int i = temp_num.length() - 1; i >= 0; --i){
        ans += int_val(temp_num[i]) * power;
        power *= 32;
    }
    return to_string(ans);
  }
  string base_32(string temp_num){
    cout << "reach" << endl;
    Bignat temp_num_big(temp_num);
    string ans;
    Bignat zero;
    Bignat base(32);
    while(temp_num_big > zero){
        cout << ans << endl;
        ans += (temp_num_big % base).get_num();
        temp_num_big = temp_num_big / base;
    }
    reverse(ans.begin(), ans.end());
    return ans;
  }
public:
  Bignat() : num(0)
  {}
  Bignat(const string new_str) : num(new_str)
  {}
  Bignat(const int new_int){
    if(new_int == 32){
        num = {1};
        return;
    }
    num = to_string(new_int);
    reverse(num.begin(), num.end());
    num = base_32(num);
    
    //reverse(num.begin(), num.end());
  }
  string get_num(){
    return num;
  }
  void print_num(){
    string temp_num = num;
    reverse(temp_num.begin(), temp_num.end());
    cout << base_10(temp_num) << endl;
  }
  
  
};

int main(){
  Bignat a("r2np");
  Bignat b("b7");
  cout << "okay" << endl;
  cout << (a + b).get_num() << endl;
  (a + b).print_num();
  (b - a).print_num();
  //cout << (a * b).get_num() << endl;
  //cout << (a / b).get_num() << endl;
}
