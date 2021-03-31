#include "hello.hpp"
#include "good_morning.hpp"

#include <iostream>
#include <vector>
#include <boost/lambda/lambda.hpp>
#include <boost/range/algorithm.hpp>

using namespace std;

void test_boost()
{
  // ref https://kaworu.jpn.org/cpp/boost::find
  vector<int> v;

  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.push_back(4);

  vector<int>::iterator it = boost::find(v, 3);
  cout << *it << endl; // 3
}

int main()
{
  hello();
  good_morning();
  test_boost();
}