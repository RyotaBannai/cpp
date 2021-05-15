#include <cmath>
#include <iostream>
#include <valarray>
using namespace std;

void use()
{
  valarray<int> va(3, 7);
  for (auto const x : va)
    cout << x << endl;

  // for (auto &x : va)
  //   x = pow(x, 2);

  // NOTE: apply は関数オブジェクトを引数として受け取ることができない
  // また lambda を与えたときにキャプチャもできない.
  auto va2 = va.apply([](int x) -> int { return pow(x, 2); });

  for (auto const &x : va2)
    cout << x << endl;

  cout << va2.sum() << endl;

  valarray<int> v3 = pow(va, va2);
  for (auto const &x : v3)
    cout << x << endl;
  // for_each(begin(v3), end(v3), [](int x) { cout << x << endl; });
}
int main() { use(); }