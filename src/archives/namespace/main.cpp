#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

namespace Parser
{
double expr(bool);
double term(bool);
double prim(bool);
} // namespace Parser

double Parser::expr(bool b) // 定義
{
  cout << "implement Parser::expr" << endl;
  return 0.0;
}

namespace N
{
struct S
{
  int i;
};
void f(S);
void g(S);
void h(int);
} // namespace N

struct Base
{
  void f(N::S);
};

struct D : Base
{
  void mf(N::S);
  void g(N::S s)
  {
    f(s);  // 基底の Base.f() を呼び出す
    mf(s); // 同 struct D の mf()
    // f(1);  // 引数に int を受け取る f() がどこにも存在しないため、エラー: error: no viable conversion from 'int' to 'N::S'
  }
};

int main()
{
  double val = Parser::expr(true); // 利用
  return 0;
}