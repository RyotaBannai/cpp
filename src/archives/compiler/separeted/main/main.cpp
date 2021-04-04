#include "parser.hpp"
#include "lexer.hpp"
#include "table.hpp"
#include "driver.hpp"
// #include <iostream> // 冗長 dc.hpp にもある
#include <sstream>

using namespace Lexer;
using namespace Table;
using namespace Driver;
using namespace Error;
using namespace Parser;

void Driver::calculate()
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