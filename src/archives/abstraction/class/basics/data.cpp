#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Date
{
  int d, m, y;
  void init(int, int, int); // 初期化
  void add_year(int n);
  void add_month(int n);
  void add_day(int n);
};
ostream &operator<<(ostream &os, const Date &d)
{
  return os << "{" << d.y << "/" << d.m << "/" << d.d << "}";
}

void Date::init(int dd, int mm, int yy)
{
  d = dd;
  m = mm;
  y = yy;
};

void Date::add_day(int num)
{
  d += num;
}

int main()
{
  Date today;
  today.init(16, 10, 1996);
  cout << today << endl;

  // Date tomorrow = today; // copy assignment
  Date tomorrow{today}; // copy instantiation
  tomorrow.add_day(1);
  cout << tomorrow << endl;

  return 0;
}