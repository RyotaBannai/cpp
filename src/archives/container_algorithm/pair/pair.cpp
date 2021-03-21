#include <string>
#include <iostream>
#include <vector>
using namespace std;

struct Entry
{
  string name;
  int number;
};

ostream &operator<<(ostream &os, const Entry &e)
{
  return os << "{\"" << e.name << "\", " << e.number << "}";
}

vector<Entry> phone_book = {
    {"David Hume", 12},
    {"Karl Popper", 34},
    {"Bertrand Arthur William Russell", 56},
};

auto ent_gt = [](const Entry &e1, const Entry &e2) { 
  cout << e1 << e2 << endl;
  return e1.number < e2.number; };

void f(const vector<Entry> &e)
{
  auto er = equal_range(e.begin(), ++e.end(), Entry{"Mark Zackerburg", 10}, ent_gt);
  for (auto p = er.first; p != er.second; ++p)
    cout << *p;
};

int main()
{
  f(phone_book);
  return 0;
}
