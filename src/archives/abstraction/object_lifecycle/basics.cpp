string ident(string arg) // string の値渡し（arg にコピーされる）
{
  return arg; // string の返却(ident() の外の呼び出し元に arg の値をムーブ)
}

int main()
{
  string s1{"Adams"}; // string を初期化(s1 を構築)
  s1 = ident(s1);     // s1 を ident() にコピー
  // ident(s1) の結果を s1 にムーブ
  // s1 の値は "Adams" になる

  string s2{"Pratchett"}; // string を初期化(s2 を構築)
  s1 = s2;                // s2 を ident() にコピー
  // s1 の結果を s2 にコピー
  // s1、s2の両方の値は "Pratchett" になる
}