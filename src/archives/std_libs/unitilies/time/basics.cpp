#include <chrono>
#include <iostream>
using namespace std;

/**
 * duration<Rep, Period>
 */
void use_duration()
{
  chrono::duration<int, milli> d{3};
  cout << d.count() << endl; // 3

  // 算術計算時には duration を使う.
  d += chrono::duration<int, milli>{5};
  cout << d.count() << endl; // 5

  d += decltype(d){5};
  cout << d.count() << endl; // 13

  d *= 2;                    // 乗算は ok
  cout << d.count() << endl; // 26
}

int main() { use_duration(); }