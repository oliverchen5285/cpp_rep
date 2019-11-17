#include <iostream>
#include <string>
#include <vector>
using namespace std;

//bad parenthesis problem that finds all possible combinations of ( and ) -- and then checks them

vector<string> solutions;

int power(int a, int b){
    int ans = 1;
    for(int i = 0; i < b; i++){
        ans = ans * a;
    }
    return ans;
}

void gen(int n){
    int pow = power(2, n-1);
    bool a[n];
    
    int temp;
    int bindigit;
    string ans;
    for(int i = 0; i < pow; i++){
        temp = i;
        for(int i = 0; i < n; i++){
            a[i] = false;
        }
        for(int j = n-1; j >= 0; j--){
            bindigit = power(2, j);
            if(bindigit <= temp){
                temp = temp - bindigit;
                a[j] = true; 
            }
        }
        /*
        cout << i << " ";
        for(int j = 0; j < n; j++){
            if(a[j] == true){
                cout << 1;
            }
            if(a[j] == false){
                cout << 0;
            }
        }
        cout << endl;
        */
        ans = "";
        for(int j = 0; j < n; j++){
            if(a[j] == true){
                ans.append("(");
            }
            if(a[j] == false){
                ans.append(")");
            }
        }
        solutions.push_back(ans);
    }
    return;
}

bool check(string a){
    int open = 0;
    bool valid = true;
    for(int i = 0; i < a.length(); i++){
        if(a[i] == '('){
            ++open;
        }
        if(a[i] == ')'){
            --open;
        }
        if(open < 0){
            valid = false;
        }
    }
    if(open != 0){
        valid = false;
    }
    return valid;
}

int main()
{
  int n;
  cin >> n;
  vector<string> working;
  gen(n);
  for(int i = 0; i < solutions.size(); i++){
      cout << solutions[i] << endl;
  }
  cout << endl;
  for(int i = 0; i < solutions.size(); i++){
      if(check(solutions[i])){
          working.push_back(solutions[i]);
          cout << solutions[i] << endl;
      }
  }
  cout << working.size() << endl;
}
