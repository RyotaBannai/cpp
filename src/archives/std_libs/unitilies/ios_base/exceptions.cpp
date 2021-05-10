#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// https://en.cppreference.com/w/cpp/io/ios_base/failure

struct Io_guard {
  istream &s;
  ios_base::iostate old_e = s.exceptions();
  Io_guard(istream &ss, ios_base::iostate e) : s{ss} { s.exceptions(s.exceptions() | e); }
  ~Io_guard() { s.exceptions(old_e); };
};

void use(istream &is)
{
  Io_guard(is, is.ios_base::badbit);
  // ....
}

int main()
{
  try {
    ifstream is("file.txt");
    use(is);

    // ...
    // cin.setstate(ios_base::badbit); // ?
    is.exceptions(is.failbit);
  }
  catch (const std::ios_base::failure &e) {
    cerr << "error: " << e.code().message() << endl; // error: unspecified iostream_category error
  }
}