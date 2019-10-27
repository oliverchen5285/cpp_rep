#include <iostream>
#include <string>
#include <math.h>
#include <bits/stdc++.h>
#include <cmath>
using namespace std;

int main()
{
  long a = 1;
  int sum;
  for(int i = 1; i <= 100; i++){
    a = a * 2;
    sum = 0;
    for(int j = 1; j <= floor(log10(a))+1; j++){
      sum = sum + ((a%(pow(10, j))) - (a%(pow(10, j-1))))/pow(10, j-1);
    }
    cout << a << " " << sum << endl;
  }
}

