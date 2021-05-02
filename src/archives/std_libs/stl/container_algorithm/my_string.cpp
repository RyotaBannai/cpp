#include <iostream>
#include <vector>
using namespace std;

int main()
{
  int b = 'b'; // 98 整数定数にキャストされる
  char c = 'c';
  cout << 'a' << b << c << endl; // a98c // cout: ostream type, cin: istream type
  /*
    cin: デフォルトでは空白類文字は読み取りを終了させる Eric Bloodaxe -> Eric
    getline(): 末尾の改行文字までの行全体を読み取る場合 Eric Bloodaxe -> Eric Bloodaxe 
  */
  return 0;
}
