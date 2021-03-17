#include <iostream>
#include <complex>
using namespace std;

/*
  $ g++ -o <name-you-want-to-give> source.cpp -> this compile with C++98
  to compile as C++11
  $ clang++ -std=c++11 -stdlib=libc++ -Weverything intro.cpp
  ref: https://stackoverflow.com/questions/14228856/how-to-compile-c-with-c11-support-in-mac-terminal
*/

static double square(double x) // 倍精度浮動小数点数
{
  return x * x;
}

void print_square(double x)
{
  cout << "the square of " << x << " is " << square(x) << endl; // cout 標準出力ストリーム
}

static void initialize_object()
{
  double d1 = 2.3;   // 2.3 で初期化
  double d2 = {2.3}; // 2.3 で初期化 // warning: constructor call from initializer list is incompatible with C++98 [-Wc++98-compat]

  complex<double> z = 1;
  complex<double> z2 = {d1, d2};
  complex<double> z3 = {1, 2};

  // auto : 型推論をしてくれる (50)
  auto b = true;
  auto ch = 'x';
  auto d = 1.2;
}

static void check_cplusplus_version()
{
  if (__cplusplus == 201703L)
    std::cout << "C++17\n";
  else if (__cplusplus == 201402L)
    std::cout << "C++14\n";
  else if (__cplusplus == 201103L)
    std::cout << "C++11\n";
  else if (__cplusplus == 199711L)
    std::cout << "C++98\n";
  else
    std::cout << "pre-standard C++\n";
}

int main()
{
  // print_square(1.234);
  initialize_object();
  // check_cplusplus_version();
}