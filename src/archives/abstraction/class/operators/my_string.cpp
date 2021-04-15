#include <iostream>
#include <new>
#include <string>
#include <list>
#include <vector>
#include <complex>
using namespace std;

/*
Details for this on 562
*/
class String {
public:
  String(); // default constructor
  String(const char* p);

  String(const String&); // copy
  String& operator=(const String&); //copy

  String(String&& x); // move
  String& operator=(String&& x); // move

  ~String() { if (short_max < sz) delete[] ptr; };

  // methods
  char& operator[](int n) { return ptr[n]; };
  char operator[](int n) const { return ptr[n]; }
  // より安全
  char& at(int n) { check(n); return ptr[n]; };
  char at(int n) const { check(n); return ptr[n]; }

private:
  static const int short_max = 15;
  int sz; // 文字数
  char* prt; // c 言語スタイルの文字列表現
  union {
    int space;
    char ch[short_max + 1]; // 末尾のナル文字のために１個分余分に確保
  }

  /*
  補助関数:
  一般的な用途を意図したものではなく、むしろ利用に危険が伴う関数、
  一方でコードの重複の削減、より良い設計、保守性の向上をもたらす
  */
  // ptr に index でアクセスする際に、out of range かどうかの範囲チェック
  void check(int n) const {
    if (n < 0 || sz <= n)
      throw std::out_of_range("String::at()");
  }

  // メモリ領域が不足した時に、新たに n size で確保
  char* expand(const char* ptr, int n) {
    char* p = new char[n];
    strcpy(p, ptr);
    return p;
  }

  void copy_from(const String& x);
  void move_from(String& x);
}

void main() {

}