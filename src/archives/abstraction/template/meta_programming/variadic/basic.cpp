#include <iostream>
#include <string>
#include <vector>

namespace Estd {
  void printf(const char *s)
  /** 書式文字列しか渡されてない場合(非書式引数が存在しない場合)に、
   * 書式指定子(%)が含まれていたら error */
  {
    if (s == nullptr)
      return;

    while (*s) {
      if (*s == '%' && *++s != '%')
        throw std::runtime_error("invalid format: missing arguments");
      std::cout << *s++;
    }
  }

  template <typename T, typename... Args> // 可変個テンプレート引数の並び：１個以上の引数
  void printf(const char *s, T value, Args... args) // 関数引数並び: 2 個以上の引数
  {
    while (s && *s) {
      if (*s == '%' && *++s != '%') {
        // エスケープされてない % (%%) 文字がきたら、% を cout する代わりに variadic 引数を cout
        // に渡す.
        std::cout << value;
        return printf(++s, args...); // args... の先頭が T value へ入り再帰的に呼び出される.
      }
      std::cout << *s++;
    }
    // 文字列が最後まで達しているのに、非書式引数が存在しているため、template が呼ばれた場合 error.
    // 本来であれば文字列だけを受け取る方の printf が呼ばれるべき
    throw std::runtime_error("extra arguments provided to printf");
  }
}

int main()
{
  Estd::printf("formatter doesn't exist.\n");
  Estd::printf("formatter exist. % \n", 12345); // \n doesn't show when its on the end.
}