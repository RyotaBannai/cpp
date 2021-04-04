#include <iostream>
#include <map>
#include <string>
using namespace std;

namespace Parser
{
double expr(bool);
double term(bool);
double prim(bool);
} // namespace Parser

namespace Lexer
{
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
namespace Table
{
extern map<string, double> table;
} // namespace Table
namespace Error
{
extern int no_of_errors;
double error(const string &s);
} // namespace Error
namespace Driver
{
void calculate();
} // namespace Driver