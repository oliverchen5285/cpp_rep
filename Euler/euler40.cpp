#include <iostream>
#include <string>
using namespace std;

int main()
{
  string a;
  for(int i = 1; i < 500000; i++){
    a = a + to_string(i);
    cout << to_string(i);
  }
  cout << endl << "size " << a.size() << endl;
  cout << (a[0]-'0') << endl;
  cout << (a[9]-'0') << endl;
  cout << (a[99]-'0') << endl;
  cout << (a[999]-'0') << endl;
  cout << (a[9999]-'0') << endl;
  cout << (a[99999]-'0') << endl;
  long ans = (a[0]-'0')*(a[9]-'0')*(a[99]-'0')*(a[999]-'0')*(a[9999]-'0')*(a[99999]-'0')*(a[999999]-'0');
  cout << "found answer!" << ans << endl;
}

