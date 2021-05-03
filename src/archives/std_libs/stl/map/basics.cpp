#include <iostream>
#include <map>
#include <string>
using namespace std;

/** sort されるため結果は同じ */
multimap<string, int> mm{{{"apple", 2}, {"pear", 2}, {"apple", 7}, {"orange", 2}, {"apple", 9}}};
const string k{"apple"};

auto use_equal_range = []() -> auto { return mm.equal_range(k); };
using M_iterator = decltype(mm)::iterator;
pair<M_iterator, M_iterator> use_pair() { return make_pair(mm.lower_bound(k), mm.upper_bound(k)); }

// using Make_pair_Ft = pair<M_iterator, M_iterator>();

// error: 'auto' not allowed in function prototype
// auto show_apple = [](Make_pair_Ft f) -> void {
auto show_apple = [](auto f) -> void {
  auto pp = f();
  if (pp.first == pp.second)
    cout << "the key not found." << endl;
  else {
    cout << "elements with value'" << k << "':\n";
    for (auto p = pp.first; p != pp.second; ++p)
      cout << p->second << ' ';
    cout << endl;
  }
};

int main()
{
  show_apple(use_equal_range);
  show_apple(use_pair);
}