#include <iostream>
#include <map>
#include <string>
using namespace std;

enum class Kind : char
{
  name,
  number,
  end,
  plus = '+',
  minus = '-',
  mul = '*',
  div = '/',
  print = ';',
  assign = '=',
  lp = '(',
  rp = ')',
};

struct Token
{
  Kind kind;
  string string_value;
  double number_value;
};

class Token_stream
{
public:
  Token get();            // 次のトークンを読み取って返却
  const Token &current(); // 最後に読み込んだトークン
};

map<string, double> table = {{{"radius", 6378.388}, {"pi", 3.1415}}};

double
expr(bool get) // 加算と減算
{
  double left = term(get);
  for (;;)
  {
    switch (ts.current().kind)
    {
    case Kind::plus:
      left += term(true);
      break;
    case Kind::minus:
      left -= term(true);
      break;
    default:
      return left;
    }
  }
}

double term(bool get) // 乗算と徐算
{
  double left = prim(get);
  for (;;)
  {
    switch (ts.current().kind)
    {
    case Kind::mul:
      left *= prim(true);
      break;
    case Kind::div:
      if (auto d = prim(true))
      {
        left /= d;
        break;
      }
      return error("divice by 0");
    default:
      return left;
    }
  }
}

double expr(bool);    // 循環参照を打破
double prim(bool get) // 一次式を処理
// 関数呼び出しの階層の下位に位置しており、実際の処理の一部を担当するためループは不要
{
  if (get)
    ts.get();
  switch (ts.current().kind)
  {
  case Kind::number:
  {
    double v = ts.current.number_value;
    ts.get();
    return v;
  }
  case Kind::name:
  {
    double &v = table[ts.current().string_value]; // 対応するものを見つける
    if (ts.get().kind == Kind::assign)            // '=' が見つかった(代入式)
      v = expr(true);
    return v;
  }
  case Kind::minus:
    return -prim(true);
  case Kind::lp:
  {
    auto e = expr(true);
    if (ts.current().kind != Kind::rp)
      return error("')' expected");
    ts.get(); // ')' を読み飛ばす
    return e;
  }
  default:
    return error("primary expected");
  }
}