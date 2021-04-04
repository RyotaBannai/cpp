#include <iostream>
#include <map>
#include <string>
using namespace std;

extern int x;
void f();
void g()
{
  f();
  cout << "the value of int x: " << x << endl;
}