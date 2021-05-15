#include <cassert>
#include <codecvt>
#include <iostream>
#include <locale>
#include <sstream>
#include <string>
using namespace std;

void use()
{
  wstring_convert<codecvt_utf8<wchar_t>> myconv;
  string s = myconv.to_bytes(L"hello\n");
  cout << s;

  wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;

  string s8 = u8"This is an UTF-8 string";
  wstring s16 = converter.from_bytes(s8); // to wstring type
  string s88 = converter.to_bytes(s16);   // to string type

  if (s8 != s88)
    cerr << "Insane!\n";
}

int main() { use(); }