#include <string>
#include <vector>
using namespace std;

template <typename T>
class Less_than
{
  const T val;

public:
  Less_than(const &T v) : val(v) {}                     // val で引数をラップ
  bool operator()(const T &x) const { return x < val; } // 実際の呼び出し時のロジック
};

Less_than<int> lti{42};
Less_than<string> lts{"Backus"};

void fct(int n, string &s)
{
  bool b1 = lti(n);
  bool b2 = lts(s);
  // ...
}

template <typename C, typename P>
int count(const C &c, P pred)
// 関数オブジェクトが true を返した回数をカウントする
{
  int cnt = 0;
  for (const auth &x : c)
    if (pred(x))
      ++cnt;
  return cnt;
}

void f(const Vector<int> &vec, int x)
{
  cout << "number of values less than " << x << ": " << count(vec, Less_than<int>{x}) << endl;
}
// by using lambda function, you can replace functor
void f(const Vector<int> &vec, int x)
{
  cout << "number of values less than " << x << ": " << count(vec, [&](int a) { return a < x; }) << endl;
}