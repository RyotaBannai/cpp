#include <iostream>
#include <string>

// function template
template <int N> constexpr int fac() { return N * fac<N - 1>(); }
template <> constexpr int fac<1>() { return 1; }
// fac() の呼び出しが、N == 1 になった時に再帰が終了

int main()
{
  constexpr int x5 = fac<5>();
  std::cout << "the result is: " << x5 << std::endl;
}