#include <array>
#include <iostream>
#include <list>
#include <new>
#include <string>
#include <vector>
using namespace std;

// primary template
template <typename T> class complex {
public:
  complex(const T &re = T{}, const T &im = T{}){};
  complex(const complex &){};
  template <typename X> complex(const complex<X> &);

  complex &operator=(const complex &);
  complex<T> &operator=(const T &);
  complex<T> &operator+=(const T &);

  template <typename X> complex<T> &operator=(const complex<X> &);
  template <typename X> complex<T> &operator+=(const complex<X> &);
};

// specialization この場合は別の定義が生成されることはない(736)
template <> class complex<float> {
public:
  // float の場合、スカラ大隠喩演算子が参照の引数を受け取ると非効率なので、値渡しできるようにする
  complex<float> &operator=(float);
  complex<float> &operator+=(float);
  //
};

int main() { complex<float> c{}; }