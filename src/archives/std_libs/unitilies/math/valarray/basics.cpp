#include <cmath>
#include <iostream>
#include <valarray>
using namespace std;

void use()
{
  valarray<int> va(3, 7);
  for (auto const x : va)
    cout << x << endl;

  // for (auto &x : va)
  //   x = pow(x, 2);

  // NOTE: apply は関数オブジェクトを引数として受け取ることができない
  // また lambda を与えたときにキャプチャもできない.
  auto va2 = va.apply([](int x) -> int { return pow(x, 2); });

  for (auto const &x : va2)
    cout << x << endl;

  cout << va2.sum() << endl;

  valarray<int> v3 = pow(va, va2);
  for (auto const &x : v3)
    cout << x << endl;
  // for_each(begin(v3), end(v3), [](int x) { cout << x << endl; });
}

void use_slice_array()
{
  // NOTE: slice(start, size, stride)
  valarray<int> va({1, 2, 3, 4, 5, 6, 7, 8, 9});
  auto v_odd = va[slice(0, va.size() / 2 + va.size() % 2, 2)]; // reference for add index
  // need const.
  slice_array<int> const &v_even = va[slice(1, va.size() / 2, 2)]; // reference for even index

  // there is no defef method for slice_array..
  v_odd = 0;
  for (auto x : va)
    cout << x << endl;
}

size_t gslice_index(const gslice &s, size_t i, size_t j)
// (i,j) から対応する添字へマッピング
{
  return s.start() + i * s.stride()[0] + j * s.stride()[1];
}

void use_gslice_array()
{
  valarray<int> va(1, 9); // 111111111

  // NOTE: (列, 行) での順で与える..!
  valarray<size_t> lengths{2, 3}; // 2 列 3 行
  valarray<size_t> strides{3, 1}; // 3 は 列に対するストライドで、1 は 行に対するストライドs

  gslice s(0, lengths, strides);
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 2; ++j) {
      size_t tar_index = gslice_index(s, i, j);
      cout << "(" << i << "," << j << ")->" << tar_index << "; \n";
      va[tar_index] = 0;
    }

  for (auto x : va)
    cout << x << ','; // 0,0,1,0,0,1,0,0,1,
  cout << endl;
}

int main()
{
  // use();
  // use_slice_array();
  use_gslice_array();
}