#include <iostream>
#include <vector>
#include <string>
using namespace std;

template <typename T>
using Iterator = typename T::iterator; // T の反復子 iterable じゃないといけない // 反復子には多くのものがあり、vector の場合は pointer　// list<Entry> の反復子は、list<Entry>::iterator

template <typename C, typename V>
vector<Iterator<C>> find_all(C &c, V v)
{
  vector<Iterator<C>> res;
  for (auto p = c.begin(); p != c.end(); ++p) // コンテンは一般的に ++ で次の pointer に移動、* 関節参照演算子で　pointer の指すオブジェクトを取得 c と基本的には同じ.
    if (*p == v)
      // cout << *p << endl;
      res.push_back(p);
  return res;
}

int main()
{
  string m{"Mary had a little lamb"}; // string::iterator type
  for (auto p : find_all(m, 'a'))
    if (*p != 'a')
      cerr << "string bug!\n";

  vector<string> ld{
      "red",
      "blue",
      "green",
      "red"};
  for (auto p : find_all(ld, "red"))
    if (*p != "red")
      cerr << "string bug!\n";
  return 0;
}
