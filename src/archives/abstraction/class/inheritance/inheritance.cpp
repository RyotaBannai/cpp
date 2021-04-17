#include <iostream>
#include <new>
#include <string>
#include <list>
#include <vector>
#include <complex>
using namespace std;

struct B1 {
  void f(int) {
    cout << "B1:int" << endl;
  }
};

struct B2 {
  void f(double) {
    cout << "B2:double" << endl;
  }
};

struct D : B1, B2 {
  using B1::f;
  using B2::f;
  void f(char) {
    cout << "D:char" << endl;
  }
};

void use(D d) {
  d.f(1);
  d.f(1.0);
  d.f('a');
}

int main() {
  use({}); // 自動で型変換が実行されるため D になる

  return 0;
}