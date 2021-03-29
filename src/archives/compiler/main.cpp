#include <iostream>
#include <map>
#include <string>
#include <type_traits>
#include <cctype> // isalpha() など
#include <utility>

using namespace std;

int no_of_errors;
double error(const string &s)
{
  no_of_errors++;
  cerr << "error: " << s << endl;
  return 1;
}

enum class Kind : char
{
  name = '0',
  number = '1',
  end = '2',
  plus = '+',
  minus = '-',
  mul = '*',
  div = '/',
  print = ';',
  nl = '\n',
  assign = '=',
  lp = '(',
  rp = ')',
};

ostream &operator<<(ostream &strm, Kind k)
{
  string k_names[] = {"name", "number", "end"};
  auto k_name = underlying_type<Kind>::type(k);
  // cout << "underlying_type: " << underlying_type<Kind>::type(k) << endl; // doesn't help..

  // show type of variable.
  // cout << "typeid is " << typeid(k_name).name() << " " << endl;

  // class enum で char として割り当てないと、underlying_type で k_names[xxx] で表示されるものの、
  // 判定ができない
  if (k_name == '0' || k_name == '1' || k_name == '2')
    return strm << k_names[k_name - '0'];
  else
    return strm << k_name;
}

//　https://stackoverflow.com/questions/11421432/how-can-i-output-the-value-of-an-enum-class-in-c11

// enum のメンバがわかっている場合には使える
// template <typename Enumeration>
// constexpr auto as_integer(Enumeration const value)
//     -> typename std::underlying_type<Enumeration>::type
// {
//   static_assert(std::is_enum<Enumeration>::value, "parameter is not of type enum or enum class");
//   return static_cast<typename std::underlying_type<Enumeration>::type>(value);
// }

struct Token
{
  Kind kind;
  string string_value;
  double number_value;
};

class Token_stream
{
public:
  Token_stream(istream &in) : ip{&in}, owns{false} {}
  Token_stream(istream *p) : ip{p}, owns{true} {}
  ~Token_stream() { close(); }

  Token get();                          // 次のトークンを読み取って返却
  const Token &current() { return ct; } // 最後に読み込んだトークン

  void set_input(istream &in)
  {
    close();
    ip = &in;
    owns = false;
  }
  void set_input(istream *p)
  {
    close();
    ip = p;
    owns = true;
  }

private:
  void close()
  {
    if (owns)
      delete ip;
  }
  istream *ip;         // 入力ストリームへのポインタ
  bool owns;           // Token_stream は istream を所有しているかどうか（所有権を持つかどうか）
  Token ct{Kind::end}; // 不注意により get() の前に current() を呼び出した時でもまともな Token が得られるようにする
};

Token Token_stream::get()
{
  char ch = 0;
  do
  {                   // \n 以外の空白をスキップ
    if (!ip->get(ch)) // get は空白文字を読み飛ばさない, get が読み取り成功時に true を返す
      return ct = {Kind::end};
  } while (ch != '\n' && isspace(ch));
  switch (ch)
  {
    // 入力終了
  case 0:
    return ct = {Kind::end}; // 代入と返却
    // 演算子、区切り文字
  case ';':
  case '\n':
  case '*':
  case '/':
  case '+':
  case '-':
  case '(':
  case ')':
  case '=':
    return ct = {static_cast<Kind>(ch)};
    // value となる数値
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
  case '.':          // 小数点を表す '.'
    ip->putback(ch); // バッファに戻して、number_value は double へと読み込むように定義ずみなので、そのまま浮動小数点数を読み取らせる
    *ip >> ct.number_value;

    // TODO: check if ct.number_value has whole value at one time.
    // cout << "got number: " << ct.number_value << endl;

    ct.kind = Kind::number;
    return ct;
    // それ以外は name と判断
  default:
    if (isalpha(ch))
    {
      ct.string_value = ch;
      while (ip->get(ch))
        if (isalnum(ch))
          ct.string_value += ch; // string_value n後ろに　ch を連結
        else
        {
          ip->putback(ch);
          break;
        }
      // TODO: check name
      cout << "name is: " << ct.string_value << endl;

      ct.kind = Kind::name;
      return ct;
    }
    error("bad token");
    return ct = {Kind::end};
  }
}

Token_stream ts{cin};

map<string, double> table;

// 循環参照を打破
double term(bool);
double prim(bool);

double expr(bool get) // 加算と減算
{
  double left = term(get);
  cout << "in expr. kind is: " << ts.current().kind << endl;
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
  cout << "in term. kind is: " << ts.current().kind << endl;
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

double prim(bool get) // 一次式を処理
// 関数呼び出しの階層の下位に位置しており、実際の処理の一部を担当するためループは不要
{
  if (get)
    ts.get();

  // cout << "in prim. kind is: " << as_integer(ts.current().kind) << endl;
  cout << "in prim. kind is: " << ts.current().kind << endl;
  switch (ts.current().kind)
  {
  case Kind::number:
  {
    double v = ts.current().number_value;
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

void calculate()
{
  for (;;)
  {
    ts.get();
    cout << "calculate.." << endl;
    if (ts.current().kind == Kind::end)
      break;
    if (ts.current().kind == Kind::print || ts.current().kind == Kind::nl)
      continue;
    cout << expr(false) << endl;
  }
}

int main()
{
  table["pi"] = 3.1415;
  table["e"] = 2.7172;

  calculate();

  return no_of_errors;
}