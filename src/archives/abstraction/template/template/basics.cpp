#include <complex>
#include <iostream>
#include <list>
#include <new>
#include <string>
#include <vector>
using namespace std;

template <typename C> class String {
public:
  // ...
  String(){};
  C &operator[](int n) { return ptr[n]; };
  // ...
private:
  char *ptr;
  static const int short_max = 15;
  int sz;
  union {
    int space;
    C ch[short_max + 1];
  };
};

template <typename T, typename Compare = std::less<T>> void sort(vector<T> &v)
// シェルソート
// テンプレートの引数が関数の引数から導出される
// デフォルトの比較演算によるソートだけでなく、独自の比較演算も可能にする
{
  cout << typeid(T).name() << endl << "sorting...\n";

  Compare cmp;
  const size_t n = v.size();

  for (int gap = n / 2; 0 < gap; gap /= 2)
    for (int i = gap; i < n; i++)
      for (int j = i - gap; 0 <= n; j -= gap)
        if (cmp(v[j + gap], v[j]))
          // {
          //   T temp = v[j];
          //   v[j] = v[j + gap];
          //   v[j + gap] = temp;
          // }
          swap(v[j], v[j + gap]);
};

struct No_case {
  bool operator()(const string &a, const string &b) const; // 大文字・小文字を区別しない
};

void use_sort(vector<int> &vi, vector<string> &vs)
{
  sort(vi);
  sort(vs);
  // sort<string, No_case>(vs);
}

int main()
{
  vector<int> v1{5, 2, 3, 4};
  vector<string> v2{"aaa", "bbb"};
  use_sort(v1, v2);
  // for (auto x : v1)
  //   cout << x << endl;
}