#include <complex>
#include <iostream>
#include <list>
#include <new>
#include <string>
#include <vector>
using namespace std;

template <typename C> class String {
public
  // ...
  String(){};
  C &operator[](int n) { return ptr[n]; };
  // ...
private:
  static const int short_max = 15;
  int sz;
  union {
    int space;
    C ch[short_max + 1];
  };
};

int main() {}