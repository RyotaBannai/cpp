#include <ctype.h>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void use_for_getline()
{
  /**
   * incomplete loop with one declaration outside.
   */
  // cin >> str doesn't accept whitespaces
  // int times;
  // cin >> times;
  // cin >> ws; // stream out any whitespace
  // for (auto p = std::make_pair(0, string{}); p.first != times && getline(cin, p.second);
  //      ++p.first) {
  //   cout << "entered: " << p.second << endl;
  // }

  /**
   * complete loop without any declaration outside.
   * immediately invoke lambda:
   * https://stackoverflow.com/questions/44868369/how-to-immediately-invoke-a-c-lambda
   * C++14 std::make_tuple, std::make_pair
   * C++17 std::tuple, std::pair
   */
  for (auto t = std::make_tuple(
           0,
           []() -> int {
             int times;
             (cin >> times).get();
             return times;
           }(),
           string{});
       get<0>(t) != get<1>(t) && getline(cin, get<2>(t)); ++get<0>(t)) {
    cout << "entered: " << get<2>(t) << ", count:" << get<1>(t) << endl;
  }
}

/**
 Other useful expressions:
 https://stackoverflow.com/questions/2687392/is-it-possible-to-declare-two-variables-of-different-types-in-a-for-loop
 1.
 std::unordered_map<K, V> m = {...};
 for (auto& [key, value] : m) {...}

 2.
 for(struct { int a; char b; } s = { 0, 'a' } ; s.a < 5 ; ++s.a)
 { std::cout << s.a << " " << s.b << std::endl; }
 */

int main() { use_for_getline(); }