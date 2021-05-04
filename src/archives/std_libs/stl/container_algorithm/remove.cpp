#include <iostream>
#include <string>
using namespace std;

void use_remove()
{
  string s{"*CamelCase*IsUgly*"};
  cout << s << endl; // *CamelCase*IsUgly*
  auto p = remove(s.begin(), s.end(), '*');
  copy(s.begin(), p, ostream_iterator<char>{cout}); // CamelCaseIsUgly
  cout << endl << s << endl;                        // CamelCaseIsUglyly*

  // マッチした箇所を詰めているだけだから後ろの文字が残る
}

int main() { use_remove(); }