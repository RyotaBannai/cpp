#include <iostream>
#include <vector>
using namespace std;

// 右辺値参照・ムーブセマンティクス:
// https://cpprefjp.github.io/lang/cpp11/rvalue_ref_and_move_semantics.html

template <typename T> struct Is_lvalue_reference {
  bool operator()() { return is_lvalue_reference<T>::value; }
};
template <typename T> struct Is_rvalue_reference {
  bool operator()() { return is_rvalue_reference<T>::value; }
};

template <typename T> using Remove_reference = typename remove_reference<T>::type;

template <typename T> void f(T &&v)
{
  cout << "lvalue? " << (Is_lvalue_reference<T>{}() ? "true" : "false") << endl;
  cout << "rvalue? " << (Is_rvalue_reference<T>{}() ? "true" : "false") << endl;

  Remove_reference<T> x = v;
  T y = v;
  ++y;
  vector<Remove_reference<T>> vec1;
  // vector<T> vec2; // T が参照であればエラー
}

struct Result {
  int c;
  Result() : c{0} {}
  void operator++() { c = c + 1; }
};

void use()
{
  Result r{};
  Result &&r2{};
  f(r);        // by reference lvalue
  f(r2);       // by reference rvalue
  f(move(r2)); // by value
  f(Result{}); //  by value
}

int main() { use(); }