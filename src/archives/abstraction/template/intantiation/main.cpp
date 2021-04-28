#include <array>
#include <iostream>
#include <list>
#include <new>
#include <string>
#include <vector>
using namespace std;

namespace N {
  class A {
  public:
    A() { cout << "class A instantiated. \n"; };
  };
  char f(A)
  {
    cout << "N::f(A)\n";
    return '0';
  };
}

char f(int)
{
  cout << "f(int)\n";
  return '0';
}

template <typename T> char g(T t)
{
  return f(t);
  return '0';
};

char f(double)
{
  cout << "f(double)\n";
  return '0';
}

int main()
{
  char c1 = g(N::A());
  char c2 = g(2);
  char c3 = g(2.1);

  /*
  N::f(A)
  f(int)
  f(int) <- f(double) は見つけられない.
  テンプレートの定義位置でスコープに入っていないし、実引数依存探索(ADL)(14.2.4)
  が、引数として組み込み型だけを受け取る広域関数を対象としないため.
  f(int) が宣言されていないと、探索できる関数が見つからずにコンパイルエラーとなる.
  */
}