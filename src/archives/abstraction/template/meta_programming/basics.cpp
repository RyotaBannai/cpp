#include <array>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// https://cpprefjp.github.io/reference/type_traits/is_integral.html
template <typename T> struct X {
  static_assert(std::is_integral<T>::value == true, "value == true, int is integral");
};

int main() { X<char>(); }