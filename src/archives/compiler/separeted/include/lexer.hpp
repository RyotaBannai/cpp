#include <iostream>
#include <string>
#include "error.hpp"

namespace Lexer
{
using namespace std;
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

struct Token
{
  Kind kind;
  string string_value;
  double number_value;
};

class Token_stream
{
private:
  void close()
  {
    if (owns)
      delete ip;
  }
  istream *ip;
  bool owns;
  Token ct{Kind::end};

public:
  Token_stream(istream &in) : ip{&in}, owns{false} {}
  Token_stream(istream *p) : ip{p}, owns{true} {}
  ~Token_stream() { close(); }
  Token get();
  Token &current();
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
};
extern Token_stream ts;
} // namespace Lexer