#include <iostream>
#include <list>
#include <string>
using namespace std;

struct Entry
{
  string name;
  int number;
};

list<Entry> phone_book = {
    {"David Hume", 12},
    {"Karl Popper", 34},
    {"Bertrand Arthur William Russell", 56},
};

// you can pass phone_book if you want > const list<Entry> &book
int get_number(const string &s)
// return number of the person with a name
{
  for (const auto &x : phone_book)
    if (x.name == s)
      return x.number;
  return 0;
}

int get_number2(const string &s)
{
  // この場合, begin() はコンテナの先頭要素へのポインタを返す
  for (auto p = phone_book.begin(); p != phone_book.end(); ++p)
    if (p->name == s)
      return p->number;
  return 0;
}

int main()
{
  string name;
  getline(cin, name);
  cout << "the input is: " << name << endl;
  int result = get_number2(name);
  if (result == 0)
    cout << "not found." << endl;
  else
    cout << "the numebr is: " << result << endl;

  return 0;
}
