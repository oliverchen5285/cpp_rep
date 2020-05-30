#include "bf.h"

int main() {
  int n;
  cin >> n;
  
  vector<string> ans_vec = bf_paren(n);
  cout << "bf: " << ans_vec.size() << endl;
}
