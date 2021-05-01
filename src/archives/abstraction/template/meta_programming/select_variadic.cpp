#include <iostream>
#include <string>

template <unsigned N, typename... Cases> struct select; // 一般のケース：具現化されることはない.

template <unsigned N, typename T, typename... Cases>
struct select<N, T, Cases...> : select<N - 1, Cases...> {
};

// 最後のケース N == 0
template <typename T, typename... Cases> struct select<0, T, Cases...> {
  using type = T;
};

template <unsigned N, typename... Cases> using Select = typename select<N, Cases...>::type;
