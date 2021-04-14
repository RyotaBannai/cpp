#include <iostream>
#include <new>
#include <string>
#include <list>
#include <vector>
#include <complex>
using namespace std;

/* std::pair のベクタを管理 */
struct Assoc {
  vector<pair<string, int>> vec; // {name, value} の pair の vector
  const int& operator[](const string&) const;
  int& operator[](const string&);
};

// const メンバにはなれない
int& Assoc::operator[](const string& s) {
  for (auto& x : vec)
    if (s == x.first)
      return x.second;
  vec.push_back({ s, 0 });
  return vec.back().second;
}

void test_out_assoc_opt() {
  Assoc values;
  string buf;
  while (cin >> buf) // 文字/ 文字列を読み取って読み取った内容を丸っと value としてカウント　
    ++values[buf];
  for (auto x : values.vec)
    cout << '{' << x.first << ',' << x.second << "}\n";
}

class Add {
  complex<double> val;
public:
  Add(complex<double> c) :val{ c } {}
  Add(double r, double i) :val{ r,i } {}

  // インスタンスを関数のように扱うことができる.
  void operator()(complex<double>& c) const { c += val; } // call operator/ application operator
};

void fn(vector<complex<double>>& vec, list<complex<double>>& lst, complex<double> z) {
  for_each(vec.begin(), vec.end(), Add{ 2,3 }); // 全ての vec に対して, complex{2, 3} を追加
  for_each(lst.begin(), lst.end(), Add{ z });
}

// sample
// void test_out_call_opt() {
//   fn(vector{ complex{1,2},complex{1,2} }, list{ complex{1,2},complex{1,2}, complex{1,2} });
// }


int main() {
  // void test_out_assoc_opt();
  auto v = vector<int>{ 2, 2 };
  cout << v.at(0) << endl;
}