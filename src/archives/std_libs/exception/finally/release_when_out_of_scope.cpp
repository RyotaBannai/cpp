#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <utility>
#include <any>
#include <stdexcept>
using namespace std;

template <typename F> // F: stands for function
struct Final_action
{
  Final_action(F f) : clean{f} {}
  ~Final_action() { clean(); }
  F clean;
  Final_action(const Final_action &) = delete;            // コピー禁止 (83): コピーコンストラクタ https://www.geeksforgeeks.org/copy-constructor-in-cpp/
  Final_action &operator=(const Final_action &) = delete; // コピー禁止 : コピー代入 https://en.cppreference.com/w/cpp/language/copy_assignment
};

template <typename F>
Final_action<F> finally(F f)
{
  return Final_action<F>(f);
}

void test()
{
  int *p = new int{7};
  int *buf = (int *)malloc(100 * sizeof(100));

  auto act1 = finally([&] {delete p; free(buf); cout<< "Goodby, Cruel world!" << endl; });

  int var = 0;
  cout << "var = " << var << endl;
  {
    var = 1;
    auto act2 = finally([&] {cout << "finally!" << endl; var=7; });
    cout << "var = " << var << endl;
  }

  cout << "var = " << var << endl;
}

int main()
{
  test();
  /*
    var = 0
    var = 1
    finally!
    var = 7
    Goodby, Cruel world!
  */
  return 0;
}