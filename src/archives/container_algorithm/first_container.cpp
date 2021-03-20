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

istream &operator>>(istream &is, Entry &e)
// {"name", number} を読み取る
{
  // get: Extracts a single character from the stream. http://www.cplusplus.com/reference/istream/istream/get/
  // cin は空白文字類を読み飛ばすが、get は読み飛ばさない

  char c, c2;
  if (is >> c && c == '{' && is >> c2 && c2 == '"') // {" で始まる
  {
    string name;
    while (is.get(c) && c != '"') // get name value
      name += c;

    if (is >> c && c == ',')
    {
      int number = 0;
      if (is >> number >> c && c == '}') // number と } を読み込む
      {
        e = {name, number};
        return is;
      }
    }
  }
  is.setstate(ios_base::failbit);
  return is;
}

static void print_book(const vector<Entry> &book)
{
  cout << "print book: \n";
  // for (int i = 0; i != book.size(); ++i)
  //   cout << book[i] << endl;
  for (auto &x : book)
    cout << x << endl;
}

int main()
{
  Entry e;
  cin >> e;
  vector<Entry> phone_book = {
      e,
      {"David Hume", 12},
      {"Karl Popper", 34},
      {"Bertrand Arthur William Russell", 56},
  };

  print_book(phone_book);
  return 0;
}
