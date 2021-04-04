#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class Date
{
  int d, m, y;
  mutable bool cache_valid;
  mutable string cache;
  void compute_cache_value() const; // mutable なキャッシュを埋める

public:
  explicit Date(int dd = 1, int mm = 1, int yy = 1970) : d{dd}, m{mm}, y{yy} {};
  string string_rep() const; // 文字列表現
  void add_year(int n);
  void add_month(int n);
  void add_day(int n);
};
void Date::compute_cache_value() const
{
  std::ostringstream d_str;
  d_str << y << "/" << m << "/" << d;
  cache = d_str.str();
}

string Date::string_rep() const
{
  if (!cache_valid)
  {
    compute_cache_value();
    cache_valid = true;
  }
  return cache;
}

ostream &operator<<(ostream &os, const Date &d)
{
  return os << d.string_rep();
}

void Date::add_day(int num)
{
  d += num;
}

int main()
{
  Date today{16, 10, 1996};
  cout << today << endl;

  // Date tomorrow = today; // copy assignment // direct  initialization!
  Date tomorrow{today}; // copy initialization
  tomorrow.add_day(1);
  cout << tomorrow << endl;

  Date date_default{};
  cout << date_default << endl;

  Date date_kw{2000};
  cout << date_kw << endl; // 1960/1/2000...

  return 0;
}