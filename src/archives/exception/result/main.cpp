#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <utility>
#include <any>
#include <stdexcept>
using namespace std;

template <class V, typename E>
class Result
{
public:
  // TODO: change to any type so that accept all value type.
  V ok;
  E err;
  Result(V ok, E err) : ok{ok}, err{err} {}
  Result(V ok) : Result{ok, E{}} {}
  Result(E err) : Result{V{}, err} {}
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
// Build in exception type: http://www.cplusplus.com/reference/exception/exception/
// catch exception: https://stackoverflow.com/questions/8480640/how-to-throw-a-c-exception
// optional: https://cpprefjp.github.io/reference/optional/optional.html
union Exception_types {
  invalid_argument ia;
  ~Exception_types(){};
};

using Result_compare = Result<bool, optional<Exception_types>>;
Result_compare compare(int a, int b)
/* Preconcdition: both args must positive numbers */
{
  // optional<exception_t> e;
  // e.emplace(invalid_argument("Received negative value"));
  Exception_types et = {invalid_argument("Received negative value")};
  auto e = make_optional(et.ia);
  if (a < 0 || b < 0)
    return Result_compare{e};
  return Result_compare{a < b};
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