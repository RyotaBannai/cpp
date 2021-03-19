#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Entry
{
  string name;
  int number;
};

ostream &operator<<(ostream &os, const Entry &e)
// iostream ライブラリは、組み込み型と標準 string の入出力に加え、
// 独自の型に対する入出力をプログラマが定義できるようにしている
{
  return os << "{\"" << e.name << "\", " << e.number << "}";
}

static void print_book(const vector<Entry> &book)
{
  // for (int i = 0; i != book.size(); ++i)
  //   cout << book[i] << endl;
  for (auto &x : book)
    cout << x << endl;
}

int main()
{
  vector<Entry> phone_book = {
      {"David Hume", 12},
      {"Karl Popper", 34},
      {"Bertrand Arthur William Russell", 56},
  };

  print_book(phone_book);
  return 0;
}
