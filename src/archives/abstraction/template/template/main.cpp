#include <complex>
#include <iostream>
#include <list>
#include <new>
#include <string>
#include <vector>
using namespace std;

// https://stackoverflow.com/questions/55619550/rvalue-for-a-stdstring-parameter

std::string global_string;

void write_value(std::string &text)
{
  cout << "called lvalue \n";
  // copy, cause allocation
  global_string = text;
}

void write_value(std::string &&text)
{
  cout << "called rvalue \n";
  global_string = move(text);
}

void test_multi_defs()
{
  string s = "writing the value";

  // called rvalue.
  write_value(string{"writing the value"});
  write_value("writing the value");

  // called lvalue
  write_value(s);

  //
  cout << s << endl;
  cout << global_string << endl;
}

template <typename T> class Xref {
public:
  // Xref(T v) { cout << "called T\n"; }
  Xref(T *p) { cout << "called pointer of T\n"; }
  Xref(T &r) { cout << "called lvalue of T\n"; }
  Xref(T &&r) { cout << "called rvalue of T\n"; }
};

class NXref {
public:
  // NXref(string v) { cout << "called T\n"; }
  NXref(string *p) { cout << "called pointer of T\n"; }
  NXref(string &r) { cout << "called lvalue of T\n"; }
  NXref(string &&r) { cout << "called rvalue of T\n"; }
};

void test_template_value_binding_xref()
{
  string s = "hello";

  Xref<string> r1 = {new string{"hello"}};
  Xref<string> r2 = {s};
  Xref<string> r3 = {"hello"};
}

void test_template_value_binding_nxref()
{
  string s = "hello";

  NXref r1 = {new string{"hello"}};
  NXref r2 = {s};
  NXref r3 = {"hello"};
}

int main()
{
  test_template_value_binding_xref();
  test_template_value_binding_nxref();
}