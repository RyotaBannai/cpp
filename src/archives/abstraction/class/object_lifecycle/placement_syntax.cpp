#include <iostream>
#include <vector>
#include <string>
#include <new>
using namespace std;

class X
{
public:
  X(int n) {}
  ~X() {}

private:
  int id;
};

int main()
{
  char *whole = new char[2 * sizeof(X)]; // メモリ領域を確保
  X *p1 = new (whole) X{8};              // 確保済みのメモリを使う
  char *seg2 = &whole[sizeof(X)];        // ひとつ後ろの領域の先頭を指す
  X *p2 = new (seg2) X{9};

  p2->~X(); // 二つ目の X オブジェクトを削除するが、whole のメモリ領域、一つ目めのオブジェクトは削除しない

  return 0;
}