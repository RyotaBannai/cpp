#include <string>
#include <iostream>
#include <vector>
using namespace std;

// https://stackoverflow.com/questions/2187648/how-can-i-use-a-stdvalarray-to-store-manipulate-a-contiguous-2d-array
template <class element_type>
class Matrix
{
public:
  Matrix(size_t width, size_t height) : m_stride(width), m_height(height), m_storage(width * height) {}

  element_type &operator()(size_t row, size_t column)
  {
    // column major
    return m_storage[std::slice(column, m_height, m_stride)][row];

    // row major
    return m_storage[std::slice(row, m_stride, m_height)][column];
  }

private:
  std::valarray<element_type> m_storage;
  size_t m_stride;
  size_t m_height;
};

template <typename T, typename U>
auto operator+(const Matrix<T> &z, const Matrix<U> &b) -> Matrix<decltype(T{} + U{})>
{
  Matrix<decltype(T{} + U{})> res;
  for (int = 0; i != a.rows(); ++i)
    for (int = 0; j != b.rows(); ++j)
      res(i, j) += a(i, j) + b(i, j);
  return res;
}