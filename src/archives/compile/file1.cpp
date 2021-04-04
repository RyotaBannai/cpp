#include <iostream>
#include <map>
#include <string>
using namespace std;

int x = 1;
void f()
{
  cout << "file1 f() " << endl;
}
void g();

int main()
{
  g();
}
