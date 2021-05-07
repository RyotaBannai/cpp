
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

int main() { use(); }