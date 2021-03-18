
#include <iostream>
using namespace std;

static void print()
{
  int v[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (auto x : v)
  {
    cout << x << endl;
  }
}

static int count_x(const char *p, char x)
/*
  string p の中に出現する文字 x をカウントしてその数を返す
*/
{
  if (p == nullptr)
    return 0;

  int count = 0;
  for (; *p != 0; ++p)
    if (*p == x)
      count++;
  return count;
}

int main()
{
  print();
  char const *my_string = "abcda";
  cout << "the result of count_x is: " << count_x(my_string, 'a') << endl;
  return 0;
}
