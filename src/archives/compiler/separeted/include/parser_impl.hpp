#include "parser.hpp"
#include "lexer.hpp"
#include "table.hpp"

using Error::error;
using namespace Lexer;
using Table::table;

// 実装者用インターフェース
namespace Parser
{
double expr(bool);
double term(bool);
double prim(bool);
} // namespace Parser