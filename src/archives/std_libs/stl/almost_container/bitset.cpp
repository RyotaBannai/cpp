#include <iostream>
#include <string>
using namespace std;

void use_bitset()
{
  bitset<8 * sizeof(int)> b = 123;
  cout << b.to_string<char, char_traits<char>, allocator<char>>() << endl;
  cout << b.to_string<char>() << endl;
  cout << b.to_string() << endl;
  cout << b << endl;
}

int main() { use_bitset(); }