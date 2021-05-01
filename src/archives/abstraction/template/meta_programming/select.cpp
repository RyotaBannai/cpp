#include <iostream>
#include <string>

class Nil {
};

template <int I, typename T1 = Nil, typename T2 = Nil, typename T3 = Nil, typename T4 = Nil>
struct select;

template <int I, typename T1 = Nil, typename T2 = Nil, typename T3 = Nil, typename T4 = Nil>
using Select = typename select<I, T1, T2, T3, T4>::type;

/**
 Specialization
 もし存在しない候補を選択した場合は、primary(general) template
 が選択されるが、特殊化が存在しない場合は　undefined error. (792)
*/
// N == 0 に対する特殊化
template <typename T1, typename T2, typename T3, typename T4> struct select<0, T1, T2, T3, T4> {
  using type = T1;
};
template <typename T1, typename T2, typename T3, typename T4> struct select<1, T1, T2, T3, T4> {
  using type = T2;
};
template <typename T1, typename T2, typename T3, typename T4> struct select<2, T1, T2, T3, T4> {
  using type = T3;
};
template <typename T1, typename T2, typename T3, typename T4> struct select<3, T1, T2, T3, T4> {
  using type = T4;
};

int main()
{
  using selected_type = Select<0, char, int, double>;
  std::cout << typeid(selected_type).name() << std::endl; // c

  // 最初に定義した select を再定義することになるためコンパイル時エラー
  // using selected_type_2 = typename select<5, char, int, double, long>::type;
  // 特殊化が定義されていないため、undefined error
  // using selected_type_2 = Select<5, char, int, double>;
}