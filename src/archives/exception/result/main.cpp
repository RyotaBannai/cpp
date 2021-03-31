#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <utility>
#include <any>
#include <stdexcept>
using namespace std;

template <typename E>
class Result
{
public:
  int ok;
  E err;
  Result(int ok, E err) : ok{ok}, err{err} {}
  Result(int ok) : Result{ok, E{}} {}
  Result(E err) : Result{0, err} {}
  string err_to_string()
  {
    // has_value, value_or などのヘルパーが用意されている
    if (err)
    {
      auto e = err.value();
      return string{typeid(e).name()} + ": " + e.what();
    }
    else // nullopt は非有効値
      return "";
  }
};

Result<optional<invalid_argument>> compare(int a, int b)
/* Preconcdition: both args must positive numbers */
{
  optional<invalid_argument> e;
  e.emplace(invalid_argument("Received negative value"));
  // auto e = make_optional(invalid_argument("Received negative value"));
  if (a < 0 || b < 0)
    return Result<decltype(e)>(e);
  return Result<decltype(e)>{a < b};
}

// void test_create_result()
// {
//   Result r{0, invalid_argument("Received negative value")};
//   // Result r1{1};
//   Result r2{runtime_error("my message")};
//   cout << r.err_to_string() << endl;
// }

int main()
{
  // test_create_result();

  Result result1 = compare(1, 1);
  Result result2 = compare(1, -2);

  if (result2.err.has_value()) // err is not {}
    cout << result2.err_to_string() << endl;
  else
    cout << result2.ok << endl;
}