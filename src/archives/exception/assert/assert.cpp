#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream> // ostringstream
#include <stdexcept>
using namespace std;

/*
  アサーションにレベルを設けて、指定されたレベルが　current_level 以下の場合に限って判定を行う.
  CURRENT_MODE と　CURRENT_LEVEL を定義することでコンパイルタイムで assertion を制御できるにする
*/

namespace Assert
{
enum class Mode
{
  throw_,
  terminate_,
  ignore_
};
constexpr Mode current_mode = Mode::throw_; // CURRENT_MODE
constexpr int current_level = 2;            //　CURRENT_LEVEL
constexpr int default_level = 1;

constexpr bool level(int n)
{
  return n <= current_level;
}

struct Error : runtime_error
{
  Error(const string &p) : runtime_error(p) {}
};

string compose(const char *file, int line, const string &message)
/* create str with filename, line no, and message */
{
  ostringstream os("(");
  os << file << "," << line << "):" << message;
  return os.str();
}

template <bool condition = level(default_level), typename Except = Error>
void dynamic(bool assertion, const string &message = "Assert::dynamic failed")
{
  if (assertion)
    return;
  if (current_mode == Mode::throw_)
    throw Except{message};
  if (current_mode == Mode::terminate_)
    std::terminate();
}

template <>
void dynamic<false, Error>(bool, const string &s) // 何も行わない
{
}

void dynamic(bool b, const string &s) // デフォルトの対処
{
  dynamic<true, Error>(b, s);
}

void dynamic(bool b) // デフォルトのメッセージ
{
  dynamic<true, Error>(b);
}
} // namespace Assert

void f(int n)
{
  const int max = 5;
  Assert::dynamic(true, "no problem");
  Assert::dynamic<Assert::level(2), Assert::Error>((1 <= n && n < max), Assert::compose(__FILE__, __LINE__, "range problem"));
  // 0 とかにすると ignore_
}

int main()
{
  f({0}); // abort
  f({1}); // ok
}