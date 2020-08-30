#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Bignat{
private:
    vector<int> n;
    
    vector<int> base_10(vector<int> temp_n){ //base 32 to 10
        vector<int> ans;
        int power = 32;
        
        for(int i = temp_n.size() -1; i >= 0; --i){
            ans.push_back(temp_n[i] * power);
            power *= 32;
        }
        return ans;
        
    }
    
    vector<int> base_32(vector<int> temp_n){ //base 10 to 32
        Bignat temp_n_big(temp_n);
        vector<int> ans;
        while(temp_n_big > Bignat()){
            ans.push_back(int(temp_n_big % Bignat(32)));
            temp_n_big = temp_n_big/Bignat(32);
        }
        return ans;
    }
    void remove_zeros(vector<int> &temp_n){
        for(int i = temp_n.size() -1; i >= 0; --i){
            
            if(temp_n[i] == 0){
                temp_n.pop_back();
            }
            else{
                return;
            }
        }
    }
    
    
public:
    Bignat() : n({0}) {}
    Bignat(const vector<int> new_n): n(new_n) {}
    Bignat(int new_n){
        if(new_n == 32){
            n = {1};
            return;
        }
        vector<int> new_n_vec;
        while(new_n > 0){
            new_n_vec.push_back(new_n % 10);
            new_n /= 10;
        }
        n = base_32(new_n_vec);
    }
    
    
    vector<int> get_n(){
        return n;
    }
    void print_n(){
        for(const auto &elem: base_10(n)){
            cout << elem;
        }
        cout << endl;
    }
    operator int(){
        vector<int> temp_n = base_10(n);
        int ans = 0;
        for(int i = temp_n.size() - 1; i >= 0; --i){
            for(int j = 0; j < (temp_n.size() - 1) - i; ++j){
                temp_n[i] *= 10;
            }
            ans += temp_n[i];
        }
        return ans;
    }
    
    bool operator >( Bignat bg2){ //had to add a loop and everything cuz vectors...
        vector<int> n2 = bg2.get_n();
        if(n.size() > n2.size()){
            return true;
        }
        if(n.size() == n2.size()){
            for(int i = 0; i < n.size(); ++i){
                if(n[i] > n2[i]){
                    return true;
                }
                if(n[i] < n2[i]){
                    return false;
                }
            }
        }
        return false;
    }
    
    bool operator <( Bignat bg2){
        vector<int> n2 = bg2.get_n();
        if(n.size() < n2.size()){
            return true;
        }
        if(n.size() == n2.size()){
            for(int i = 0; i < n.size(); ++i){
                if(n[i] < n2[i]){
                    return true;
                }
                if(n[i] > n2[i]){
                    return false;
                }
            }
        }
        return false;
    }
    
    Bignat operator +( Bignat bg2){
        cout << "yay" << endl;
        vector<int> n2 = bg2.get_n();
        //n2 = base_32(n2); //make this function
        
        vector<int> ans;
        int carry = 0;
        for(int i = 0; i <= max(n.size(), n2.size()); ++i){ //goes over by 1 for potential carry
            int digit = 0;
            digit += (i < n.size())? n[i] : 0;
            digit += (i < n2.size())? n2[i] : 0;
            digit += carry;
            
            carry = digit/32; //base 32
            digit %= 32;
            ans.push_back(digit);
        }
        cout << ":)" << endl;
        remove_zeros(ans);
        reverse(ans.begin(), ans.end());
        return Bignat(ans); //make this function
    }
    
    Bignat operator -( Bignat b2){ //n has to be greater than n2
        vector<int> n2 = b2.get_n();
        n2 = base_32(n2); //make this function
        
        vector<int> ans;
        for(int i = 0; i < n.size(); ++i){
            int digit = n[i] - (i < n2.size())? n2[i]: 0;
            if(digit < 0){
                digit += 32;
                n[i+1] -= 1;
            }
            ans.push_back(digit);
        }
        remove_zeros(ans);
        reverse(ans.begin(), ans.end());
        return Bignat(base_10(ans));
    }
    
    Bignat operator *( Bignat b2){
        vector<int> n2 = b2.get_n();
        n2 = base_32(n2); //make this function
        
        vector<int> ans = {0};
        for(int i = 0; i < n.size(); ++i){
            vector<int> digit_ans;
            int carry = 0;
            for(int j = 0; j < n2.size() + 1; ++j){
                int digit = n[i] * (j < n2.size())? n2[i]: 0;
                carry = digit/32;
                digit %= 32;
                digit_ans.push_back(digit);
            }
            remove_zeros(digit_ans);
            reverse(digit_ans.begin(), digit_ans.end());
            for(int j = 0; j < i; ++j){
                digit_ans.push_back(0);
            }
            ans = (Bignat(ans) + Bignat(digit_ans)).get_n();
        }
        return Bignat(ans);
    }
    
    Bignat operator /( Bignat b2){
        vector<int> n2 = b2.get_n();
        n2 = base_32(n2); //make this function
        reverse(n.begin(), n.end());
        reverse(n2.begin(), n2.end());
        
        vector<int> ans = {0};
        for(int i = n.size(); i <= n2.size(); ++i){
            Bignat dividend(vector<int>(n2.begin(), n2.begin() + i));
            int digit = 0;
            for(int j = 31; j >= 0; --j){
                Bignat prod = Bignat(n) * Bignat(j);
                
                if(prod <= dividend){
                    digit = j;
                    
                    int n2_size = n2.size();
                    n2.erase(n2.begin(), n2.begin() + i);
                    Bignat quotient = dividend - prod;
                    vector<int> quotient_vec = quotient.get_n();
                    for(int i = quotient_vec.size() - 1; i >= 0; --i){
                        n2.insert(n2.begin(), quotient_vec[i]);
                    }
                    i -= n2_size - n2.size();
                    break;
                }
            }
            ans.push_back(digit);
        }
        reverse(ans.begin(), ans.end());
        remove_zeros(ans);
        reverse(ans.begin(), ans.end());
        
        reverse(n.begin(), n.end());
        reverse(n2.begin(), n2.end());
        return Bignat(ans);
    }
    Bignat operator %(const Bignat b2){
        //Bignat n_big(n); //how to use "this" keyword?
        return *this - ((*this / b2) * b2);
    }
};


int main(){
    vector<int> a_vec = {27, 3};
    vector<int> b_vec = {23};
    Bignat a(a_vec);
    Bignat b(b_vec);
    cout << "reached" << endl;
    (a + b).print_n();
}
