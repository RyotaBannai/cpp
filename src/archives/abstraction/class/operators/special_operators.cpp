#include <iostream>
#include <new>
#include <string>
#include <vector>
using namespace std;

/* std::pair のベクタを管理 */
struct Assoc {
  vector<pair<string, int>> vec; // {name, value} の pair の vector
  const int& operator[](const string&) const;
  int& operator[](const string&);
};

// const メンバにはなれない
int& Assoc::operator[](const string& s) {
  for (auto x : vec)
    if (s == x.first)
      return x.second;
  vec.push_back({ s, 0 });
  return vec.back().second;
}

int main() {
  Assoc values;
  string buf;
  while (cin >> buf) // 文字/ 文字列を読み取って読み取った内容を丸っと value としてカウント　
    ++values[buf];
  for (auto x : values.vec)
    cout << '{' << x.first << ',' << x.second << "}\n";
}