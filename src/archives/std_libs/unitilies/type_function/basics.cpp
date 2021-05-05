#include <iostream>
#include <utility>
#include <vector>
using namespace std;

// 右辺値参照・ムーブセマンティクス:
// https://cpprefjp.github.io/lang/cpp11/rvalue_ref_and_move_semantics.html
// https://en.cppreference.com/w/cpp/types/is_lvalue_reference

template <typename T> struct Is_lvalue_reference {
  bool operator()() { return is_lvalue_reference<T>::value; }
};
template <typename T> struct Is_rvalue_reference {
  bool operator()() { return is_rvalue_reference<T>::value; }
};

template <typename T> using Remove_reference = typename remove_reference<T>::type;

template <typename T> void f(T &&v)
// even rvalue implicitly converted to lvalue.
{
  cout << "lvalue? " << (Is_lvalue_reference<T>{}() ? "true" : "false") << endl;
  cout << "rvalue? " << (Is_rvalue_reference<T>{}() ? "true" : "false") << endl;
  // cout << "rvalue? " << (Is_rvalue_reference<Remove_reference<T> &&>{}() ? "true" : "false")
  //      << endl; // recreate rvalue.

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
  auto r3 = std::forward<Result>({});
  f(r);        // by reference lvalue
  f(r2);       // by reference lvalue
  f(move(r2)); // by value
  f(r3);       // by by reference lvalue
  f(Result{}); //  by value
}

void use_swap()
{
  /*
  template <class T>
  void swap(T& a, T& b) {
    T t = std::move(a);
    a = std::move(b);
    b = std::move(t);
  }
  */
  vector<int> v1{1, 3};
  vector<int> v2{2, 4};
  std::swap(v1, v2);

  for (auto x : v1)
    cout << x << endl;
  for (auto x : v2)
    cout << x << endl;
}

int main()
{
  // use();
  use_swap();
}