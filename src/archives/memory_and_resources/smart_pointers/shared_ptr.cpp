#include <iostream>
#include <memory>
#include <string>
using namespace std;

/** with mutex lock: https://en.cppreference.com/w/cpp/memory/shared_ptr*/
struct X {
  ~X() { cout << "X dtor\n"; }
};
struct Y {
  ~Y() { cout << "Y dtor\n"; }
};

void use_shared_ptr()
{
  shared_ptr<void> p(new X());
  p.reset(new Y());

  cout << p.use_count() << endl; // 1
  auto p2 = p;                   // increment shared count.
  cout << p.use_count() << endl; // 2
}

int main() { use_shared_ptr(); }