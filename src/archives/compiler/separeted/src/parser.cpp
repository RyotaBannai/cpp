#include "parser_impl.hpp"

double Parser::term(bool);
double Parser::prim(bool);
double Parser::expr(bool get)
{
  double left = Parser::term(get);
  // cout << "in expr. kind is: " << ts.current().kind << endl;
  for (;;)
  {
    switch (ts.current().kind)
    {
    case Kind::plus:
      left += Parser::term(true);
      break;
    case Kind::minus:
      left -= Parser::term(true);
      break;
    default:
      return left;
    }
  }
}

double Parser::term(bool get)
{
  double left = Parser::prim(get);
  for (;;)
  {
    switch (ts.current().kind)
    {
    case Kind::mul:
      left *= Parser::prim(true);
      break;
    case Kind::div:
      if (auto d = Parser::prim(true))
      {
        left /= d;
        break;
      }
      return Error::error("divice by 0");
    default:
      return left;
    }
  }
}

double Parser::prim(bool get)
{
  if (get)
    ts.get();
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
    double &v = table[ts.current().string_value];
    if (ts.get().kind == Kind::assign)
      v = Parser::expr(true);
    return v;
  }
  case Kind::minus:
    return -Parser::prim(true);
  case Kind::lp:
  {
    auto e = expr(true);
    if (ts.current().kind != Kind::rp)
      return Error::error("')' expected");
    ts.get();
    return e;
  }
  default:
    return Error::error("primary expected");
  }
}