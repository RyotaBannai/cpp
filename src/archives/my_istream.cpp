#include <iostream>
#include <locale>
#include <string>
using namespace std;

// 入力の先頭を大文字にしてから文字列として読み込む
string get_word(istream &is)
{
  string s;
  char c;
  if (is >> c)
  {
    // put_back: 指定した1文字をストリームバッファの入力に戻す
    // unget: 最後に読み取った1文字をストリームバッファの入力に戻す
    // 大文字にしてから put_back で戻す
    is.putback(toupper(c, is.getloc()));
    is >> s;
  }
  return s;
}
int main()
{
  cout << get_word(cin) << endl;
  return 0;
}