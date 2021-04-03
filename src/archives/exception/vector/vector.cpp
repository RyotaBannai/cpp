#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

/* 標準 vector の簡易サンプル */

template <typename T, typename A = allocator<T>>
class vector
{
private:
  // elem の後ろに'予備用空間'もあるため、last != space である
  T *elem;  // 確保領域の先頭
  T *space; // 要素のシーケンスの終端で拡張用領域の先頭
  T *last;  // 確保ずみ領域の終端
  A alloc;  // アロケータ

public:
  using size_type = typename A::size_type;                           // vector の要素数用の型
  explicit vector(size_type n, const T &val = T(), const A & = A()); // n 個の要素を val で初期化数する int 型なら 0 など

  vector(const vector &a);            // copy constructor
  vector &operator=(const vector &a); // copy assignment

  vector(const vector &&a);            // move constructor
  vector &operator=(const vector &&a); // move assignment

  ~vector();

  size_type size() const {return space - elem};
  size_type capacity() const {return last - elem}; // 予備用空間も含めた last から先頭を引くことで capacity を返す
  void reserve(size_type n);                       // = capacity となるようにメモリを確保

  void resize(size_type n, const T & = {}); // 要素数を n へ変更
  void push_back(const &T);                 // 末尾に要素を追加
}

template <typename T, typename A>
vector<T, A>::vector(size_type n, const T &val, const A &a) : alloc{a} // alloc メンバを初期化
{
  elem = alloc.allocate(n); // n 要素分確保
  space = elem + n;
  for (T *p = elem; p != last; ++p)
    a.construct(p, val); // p のポインタの位置を加算して順に初期値を適用（要素の構築）

  /* 問題点： val はコピーされるが、このコピーに失敗した時に、それまでに作成された val はメモリの残りメモリリークが発生する
     解決法として、それまで作成したオブジェクトを削除することである
  */
  // iterator p;
  // try
  // {
  //   iterator end = elem + n;
  //   for (p = elem; p != end; ++p)
  //     a.construct(p, val)
  // }
  // catch (...)
  // {
  //   for (iterator q = elem; q != p; ++q)
  //     alloc.destroy(q);
  //   alloc.deallocate(n);
  //   throw;
  // }

  /* for で解体している部分は std::uninitialized_fill() を使うことで簡潔化できる*/
  // try
  // {
  //   uninitialized_fill(elem, elem + n, val);
  //   space = last = elem + n;
  // }
  // catch (...)
  // {
  //   alloc.deallocate(elem, n);
  //   throw
  // }
}

// 上の実装は std::uninitialized_fill() と同等の実装　(386)

template <typename For, typename T>
void uninitialized_fill(For beg, For end, const T &x)
{
  For p;
  try
  {
    for (p = beg; p != end; ++p)
      ::new (static_cast<void *>(&*p)) T(x); // *p の中に x のコピーを構築
  }
  catch (...)
  {
    for (For q = beg; q != p; ++q)
      (&*q)->~T();
    throw;
  }
}

int main()
{
  // vector<int> v = vector{1, 3};
}