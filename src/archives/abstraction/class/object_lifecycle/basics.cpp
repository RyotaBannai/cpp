string ident(string arg) // string の値渡し（arg にコピーされる）
{
  return arg; // string の返却(ident() の外の呼び出し元に arg の値をムーブ)
}

int main()
{
  string s1{"Adams"}; // string を初期化(s1 を構築)
  s1 = ident(s1);     // s1 を ident() にコピー // s1 の値を arg にコピー. この際にもコピーコンストラクタが呼び出される // arg から 一時変数 1 へ move され、その後外部変数へ代入するために　ident() の呼び出し結果をさらに別の一時変数 2 に対して move する. その後その一時変数から s1 へ move される. main のスコープを抜けると、s1, s2, 一時変数 2 を解放する(デストラクタ)が、一時変数 1 に対しては何も行わない.
  // ident(s1) の結果を s1 にムーブ
  // s1 の値は "Adams" になる

  string s2{"Pratchett"}; // string を初期化(s2 を構築)
  s1 = s2;                // s2 を ident() にコピー // コピー代入される（コピーコンストラクタと区別）
  // s1 の結果を s2 にコピー
  // s1、s2の両方の値は "Pratchett" になる
}