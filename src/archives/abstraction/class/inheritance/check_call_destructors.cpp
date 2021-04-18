#include <iostream>
#include <new>
#include <string>
#include <list>
#include <vector>
#include <complex>
using namespace std;


/*
  https://www.cs.technion.ac.il/users/yechiel/c++-faq/calling-base-dtor.html
*/
class Member {
public:
  ~Member() {
    cout << "call Member destructor" << endl;
  };
};

class Base {
public:
  //  virtual ~Base() = default;
  virtual ~Base() {
    cout << "call Base destructor" << endl;
  };
};

class Derived : public Base {
public:
  ~Derived();
private:
  Member m_;
};

Derived::~Derived() {
  cout << "call Derived destructor" << endl;
};

void use(Base* b) {
  delete b;
}

int main() {
  auto d = new Derived;
  use(d);
}