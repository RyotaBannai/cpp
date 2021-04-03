#include <memory>
#include <iostream>
#include <string>
using namespace std;

/* https://en.cppreference.com/w/cpp/memory/allocator */
int main()
{
  /* allocator for int */
  allocator<int> a1;       // default allocator for ints
  int *a = a1.allocate(1); // space for one int // must be a pointer
  a1.construct(a, 7);      // a は int pointer

  cout << *a << endl;
  // cout << a[0] << endl;
  cout << typeid(a).name() << endl;

  /* allocator for string, obtained by rebinding from the type of a1 */
  decltype(a1)::rebind<string>::other a2_1;
  string *s = a2_1.allocate(1);
  a2_1.construct(s, "abcde");

  cout << *s << endl; // abcde

  /* allocator for string, obtained by rebinding from the type of a1 via callocator_traits*/
  allocator_traits<decltype(a1)>::rebind_alloc<string> a2_2;
  string *s2 = a2_2.allocate(2); // space for 2 strings.
  a2_2.construct(s2, "fghij");
  a2_2.construct(s2 + 1, "klmno");

  cout << s2[0] << ", " << s2[1] << endl; // fghij, klmno
}