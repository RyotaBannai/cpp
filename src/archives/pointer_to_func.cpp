#include <iostream>
#include <map>
#include <string>
using namespace std;

void error(string s)
{
  cout << s << endl;
}

void (*efct)(string); // string 引数を受け取って何も返却しない(void)関数へのポインタ // error と同じ型であるところに注目

int main()
/*
  関数へのポインタを使うときは、* 参照はずしは不要だし、
  関数へのポインタを取得するときの & も省略可能である.

  関数へのポインタを使うことで, 
  → 別々の関数を条件によって取り替えて、同じ関数名で実行できる.
  ただし、引数型が完全に一致しなければならない（reinterpret_cast で変換は可能だが、基本的にはやらない方が良い）
*/
{
  // efct = &error; // 明示的にアドレス演算子を使っても良い
  efct = error;
  // (*efct)("error"); // 明示的に参照はずしをしても良い
  efct("error");
  return 0;
}
