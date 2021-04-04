#include "dc.hpp"
#include <iostream>
#include <cctype>

Lexer::Token_stream Lexer::ts{cin};
Lexer::Token &Lexer::Token_stream::current() { return ct; }
Lexer::Token Lexer::Token_stream::get()
{
  char ch = 0;
  do
  {                   // \n 以外の空白をスキップ
    if (!ip->get(ch)) // get は空白文字を読み飛ばさない, get が読み取り成功時に true を返す
      return ct = {Kind::end};
  } while (ch != '\n' && isspace(ch));
  switch (ch)
  {
    // 入力終了
  case 0:
    return ct = {Kind::end}; // 代入と返却
    // 演算子、区切り文字
  case ';':
  case '\n':
  case '*':
  case '/':
  case '+':
  case '-':
  case '(':
  case ')':
  case '=':
    return ct = {static_cast<Kind>(ch)};
    // value となる数値
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
  case '.':          // 小数点を表す '.'
    ip->putback(ch); // バッファに戻して、number_value は double へと読み込むように定義ずみなので、そのまま浮動小数点数を読み取らせる
    *ip >> ct.number_value;

    // TODO: check if ct.number_value has whole value at one time.
    // cout << "got number: " << ct.number_value << endl;

    ct.kind = Kind::number;
    return ct;
    // それ以外は name と判断
  default:
    if (isalpha(ch))
    {
      ct.string_value = ch;
      while (ip->get(ch))
        if (isalnum(ch))
          ct.string_value += ch; // string_value n後ろに　ch を連結
        else
        {
          ip->putback(ch);
          break;
        }
      // TODO: check name
      cout << "name is: " << ct.string_value << endl;

      ct.kind = Kind::name;
      return ct;
    }
    Error::error("bad token");
    return ct = {Kind::end};
  }
}