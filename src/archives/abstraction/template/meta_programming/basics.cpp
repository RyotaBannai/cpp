#include <array>
#include <iostream>
#include <string>
#include <vector>

// https://cpprefjp.github.io/reference/type_traits/is_integral.html
template <typename T> struct X {
  static_assert(std::is_integral<T>::value == true, "value == true, int is integral");
};

void use_pred() { X<char>(); }

// primary template
template <bool C, typename T, typename F> struct conditional {
  using type = T;
  void func() { std::cout << "use primary template \n"; }
};

// specialization
template <typename T, typename F> struct conditional<false, T, F> {
  using type = F;
  void func() { std::cout << "use specialization \n"; }
};

int main()
{
  // generate type
  typename conditional<(std::is_integral<int>::value), int, std::string>::type New_T;

  // use struct
  // conditional<(std::is_integral<int>::value), int, std::string> nt{};
  // nt.func();

  // デフォルトオブジェクトを呼び出して、それを呼び出す.
  // conditional<(std::is_integral<int>::value), int, std::string> {}(99)
  // 他の方法としては、My_cond<T>() ? First_obj{}(99) : Second_obj{}(99);
}
/*
  check: (791)
  template <typename T> constexpr bool Is_integral() { return std::is_integral<T>::value; } // (787)
  template <bool B, typename T, typename F>
  using Conditional = typename std::conditional<B, T, F>::type;
  typename Conditional<(Is_integral<T>()), X, Y> New_T;
*/