#include <iostream>
#include <string>
using namespace std;

//recursive without memoization

int recurs(int a, int b){
    if(a == 0 && b == 0){
        return 1;
    }
    int first;
    int second;
    if(a == 0){
        first = 0;
    }
    else{
        first = recurs(a-1, b);
    }
    if(b == 0){
        second = 0;
    }
    else{
        second = recurs(a, b-1);
    }
    return first + second;
}

int main()
{
  int a, b;
  cin >> a >> b;
  cout << recurs(a, b) << endl;
}
