#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using Bounds = pair<vector<int>::iterator, vector<int>::iterator>;

bool my_greater(int i, int j) { return i > j; }

void print_vector_int(const vector<int> v)
{
  for (auto x = v.begin(); x != v.end(); ++x)
    cout << *x << (x != --v.end() ? ',' : ' '); // do not show comman at the end.
  cout << endl;
}

void print_bounds_int(const Bounds bs)
{
  for (auto p = bs.first; p != bs.second; ++p)
    cout << *p << (p != bs.second - 1 ? ',' : ' '); // pair are positions. (index)
  cout << endl;
}

int main()
{
  int my_ints[] = {10, 20, 30, 30, 20, 10, 10, 20};
  vector<int> v(my_ints, my_ints + 8);
  print_vector_int(v); // 10,20,30,30,20,10,10,20
  Bounds bounds;

  // using default comparison
  sort(v.begin(), v.end());
  print_vector_int(v);                                   // 10,10,10,20,20,20,30,30
  print_bounds_int(equal_range(v.begin(), v.end(), 20)); // 20, 20, 20

  // using "mygreater" as comp
  sort(v.begin(), v.end(), my_greater);
  print_vector_int(v); // 30,30,20,20,20,10,10,10
  bounds = equal_range(v.begin(), v.end(), 20, my_greater);
  print_bounds_int(bounds); // 20,20,20

  // bounds at positions 2 and 5 [first, second)
  cout << "bounds at positions " << (bounds.first - v.begin());
  cout << " and " << (bounds.second - v.begin()) << '\n';

  return 0;
}
