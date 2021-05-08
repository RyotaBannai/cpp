#include <algorithm>
#include <cctype>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

void use()
{
  /**
   * cin から文字列を受け付けると、それまで保持していた内容を空にして、
   * 読み取った内容を保持するために拡張される.
   */
  string s{"hello"};
  cin >> s;
  cout << s << endl;

  /**
   * 連続で読み込みを実行.
   */
  string first_name;
  string last_name;
  cin >> first_name >> last_name;
  cout << first_name << last_name << endl;
}

void stl_list()
{
  string s{"Hello"};
  auto is_lower = [](char c) { return islower(c); };
  auto p = find_if(s.begin(), s.end(), is_lower); // why can't I pass std::islower instead.
  cout << *p << endl;                             // e
}

void use_replace()
{
  string attr{"Sample DB"};
  string msg{"You have failed to connect DB: [%attribute%]. Please retry later."};
  // position int
  auto pos = msg.find("[%");
  auto n = msg.find("%]") + 1;         // because length of two but position is of first char
  msg.replace(pos, n - pos + 1, attr); // because pos begins from 0
  cout << msg << endl;
  cout << string::npos << endl;

  // auto b = find_if(msg.begin(), msg.end(), [attr](char c) { return ; });
}

int main()
{
  // use();
  // stl_list();
  use_replace();
}