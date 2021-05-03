#include <iostream>
#include <string>
#include <vector>
using namespace std;

// no debug option -> Segmentation fault: 11 at l.14
// #define NDEBUG
// #include <cassert>

template <typename T> void test(vector<T *> &v)
{
  for (auto p : v) {
    assert(p != nullptr);
    cout << p->value() << endl;
  }
}

template <typename T> struct Container {
  Container(T v) : v{v} {};
  T v;
  T value() { return v; }
};

int main()
{
  using My_container = Container<int>;
  My_container cv1{1}, cv2{2};
  vector<My_container *> cv{&cv1, &cv2, nullptr};
  test(cv);
}