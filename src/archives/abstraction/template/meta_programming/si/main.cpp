#include <iostream>
#include <string>
#include <vector>

template <int M, int K, int S> struct Unit {
  enum { m = M, kg = K, s = S };
};
using M = Unit<1, 0, 0>;     // meter
using K = Unit<0, 1, 0>;     // kilogram
using S = Unit<0, 0, 1>;     // second
using MpS = Unit<1, 0, -1>;  // speed m/s
using MpS2 = Unit<1, 0, -2>; // acceleration m/(s*s) // also, the unit of 2 means 's*s'

/* Unit を計算するための型関数 Unit_plus, Unit_minus を定義 */
template <typename U1, typename U2> struct Uplus {
  using type = Unit<U1::m + U2::m, U1::kg + U2::kg, U1::s + U2::s>;
};
template <typename U1, typename U2> struct Uminus {
  using type = Unit<U1::m - U2::m, U1::kg - U2::kg, U1::s - U2::s>;
};

template <typename U1, typename U2> using Unit_plus = typename Uplus<U1, U2>::type;
template <typename U1, typename U2> using Unit_minus = typename Uminus<U1, U2>::type;

template <typename U> struct Quantity {
  double val;
  explicit constexpr Quantity(double d) : val{d} {}
};

// ユーザリテラルを定義
constexpr Quantity<M> operator"" _m(long double d) { return Quantity<M>{d}; };
constexpr Quantity<Kg> operator"" _k(long double d) { return Quantity<Kg>{d}; };
constexpr Quantity<S> operator"" _s(long double d) { return Quantity<S>{d}; };

int main()
{
  auto distance = 10.9_m;
  auto time = 20.5_s;
  auto speed = distance / time;
}