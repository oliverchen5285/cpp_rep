  /*
  string divide(string num1, string num2){
    string ans = "";

  }
  */
public:
  Bigint(const string new_num):
    num(new_num)
  {}
  string get_num(){
    return num;
  }
  Bigint operator + (Bigint num2){
    return Bigint(add(num, num2.get_num()));
  }

  Bigint operator - (Bigint num2){
    return Bigint(subtract(num, num2.get_num()));
  }
  Bigint operator * (Bigint num2){
    return Bigint(multiply(num, num2.get_num()));
  }
};

int main() {
  Bigint a("1230"), b("719");
  Bigint c = a + b;
  cout << c.get_num() << endl;
  c = a - b;
  cout << c.get_num() << endl;
  c = a * b;
  cout << c.get_num() << endl;
  return 0;
}
