#include <iostream>
#include <new>
#include <string>
#include <list>
#include <vector>
#include <complex>
using namespace std;


class Storable {
public:
  Storable(const string& s) : file_name{ s } {};
  virtual void read() = 0;
  virtual ~Storable() {};
protected:
  string file_name;
  // Storable(const Storable&) = delete;
  // Storable& operator=(const Storable&) = delete;
};

class Component : public virtual Storable {
public:
  Component(const string& s) : Storable{ s } {};
};

class Transmitter : public Component {
public:
  Transmitter(const string& s) : Storable{ s }, Component{ s } {};
  void read() override;
  ~Transmitter() override = default;
};
void Transmitter::read() {}

class Receiver : public Component {
public:
  Receiver(const string& s) : Storable{ s }, Component{ s } {};
  void read() override;
  ~Receiver() override = default;
};
void Receiver::read() {}

class Radio : public Transmitter, public Receiver {
public:
  // error: type 'Component' is not a direct or virtual base of 'Radio'
    // Component{ s }
  Radio(const string& s) : Storable{ s }, Transmitter{ s }, Receiver{ s }{};
  void read() override;
  ~Radio() override = default;
};

void Radio::read() {}


void use(Storable* ps) {
  if (Component* pc = dynamic_cast<Component*>(ps)) {
    // Component を持っている
    cout << "success to cast" << endl;
  } else {
    // Component を持っていない
    cout << "fail to cast" << endl;
  }
}

int main() {
  /*
    goes into else {} because cast doesn't know which Component class to cast from Storable object..
  */
  Radio r{ "/var/log/log.txt" };
  use(&r);

  return 0;
}