#include <iostream>
#include "Vector.h"

using namespace std;

/*
` compile as the way C does.
  $ clang++ -std=c++11 -stdlib=libc++ -Weverything user.cpp Vector.cpp Vector.h
*/

static double read_and_sum(int s)
{
  Vector v(s);
  for (int i = 0; i != s; ++i)
    cin >> v[i];
  double sum = 0;
  for (int i = 0; i != s; ++i)
    sum += v[i];

  return sum;
}

int main()
{
  double result = read_and_sum(3);
  cout << "the result of read_and_sum " << result << endl;
}