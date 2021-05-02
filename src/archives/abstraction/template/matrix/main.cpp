#include <iostream>
#include <string>
#include <vector>

/** Enable_if */
// template <bool B, typename T = void> struct std::enable_if {
//   // typedef void (&MyFunc)(int,int); or using MyFunc = void(int,int);
//   // typedef T type;
//   using T = type;
// };
// template <typename T> struct std::enable_if<false, T> {
// };
template <bool B, typename T = void> using Enable_if = std::enable_if_t<B, T>;

template <typename T, size_t N> class Matrix {
public:
  static constexpr size_t order = N;
  using value_type = T;
  using iterator = typename std::vector<T>::iterator;
  using const_iterator = typename std::vector<T>::const_iterator;

  Matrix() = default;
  Matrix(Matrix &&) = default; // move
  Matrix &operator=(Matrix &&) = default;
  Matrix(const Matrix &) = default; // copy
  Matrix &operator=(const Matrix &&) = default;
  ~Matrix() = default;

  template <typename U> Matrix(const Matrix_ref<U, N> &);            // Matrix_ref から構築
  template <typename U> Matrix &operator=(const Matrix_ref<U, N> &); // Matrix_ref を代入

  template <typename... Exts> explicit Matrix(Exts... exts); // エクステントを指定

  Matrix(Matrix_initializer<T, N>);                  // 並びでの初期化
  Matrix &operator=(const Matrix_initializer<T, N>); // 並びを代入

  // 要素の並びによる'初期化'以外に {} を利用しない. つまり代入による書き変えを提供しない
  // そのため、エクステントの初期化では () の利用が強制する
  template <typename U> Matrix(std::initializer_list<U>) = delete;
  template <typename U> Matrix &operator=(std::initializer_list<U>) = delete;

  size_t extent(size_t n) const { return desc.extends[n]; }  // n 次元中の要素数
  size_t size() const { return elems.size(); }               // 全要素数
  const Matrix_slice<N> &descriptor() const { return desc; } // 添字のためのスライス

  T *data() { return elems.data(); } // flat な要素アクセス
  const T *data() const { return elems.data(); }

  /** 添字演算、スライシング*/
  template <typename... Args>
  Enable_if<Matrix_impl::Requesting_element<Args...>(), T &> operator()(Args... args);
  template <typename... Args>
  Enable_if<Matrix_impl::Requesting_element<Args...>(), const T &> operator()(Args... args) const;

  // m(s1, s2, s3) にスライスによる添字
  template <typename... Args>
  Enable_if<Matrix_impl::Requesting_element<Args...>(), Matrix_ref<T, N>>
  operator()(const Args &...args);
  template <typename... Args>
  Enable_if<Matrix_impl::Requesting_element<Args...>(), Matrix_ref<const T, N>>
  operator()(const Args &...args) const;

  Matrix_ref<T, N - 1> operator[](size_t i) { return row(i); }; // m[i] 行アクセス
  Matrix_ref<const T, N - 1> operator[](size_t i) const { return row(i); };

  Matrix_ref<T, N - 1> row(size_t n); // 行アクセス
  Matrix_ref<const T, N - 1> row(size_t n) const;

  Matrix_ref<T, N - 1> col(size_t n); // 列アクセス
  Matrix_ref<const T, N - 1> col(size_t n) const;

private:
  Matrix_slice<N> desc; // N 次元中の範囲を定義するスライス
  std::vector<T> elems; // 要素
};

/** constructors */
// from extent
// exts... をコピーし、elem size 分の vector を確保する　
template <typename T, size_t N>
template <typename... Exts>
Matrix<T, N>::Matrix(Exts... exts) : desc{exts...}, elems(desc.size)
{
}

// from Matrix_initializer
// Matrix_initializer は適切な深さでいれことなった initializer_list (830)
// エクステントは Matrix_impl 名前空間の derive_extents によって導出し、その要素数は compute_strides
// で計算. insert_flat で要素を elems に格納
template <typename T, size_t N> Matrix<T, N>::Matrix(Matrix_initializer<T, N> init)
{
  desc.extents = Matrix_impl::derive_extents(init); // 初期化子並びに基づいてエクステントを導出　
  Matrix_impl::compute_strides(desc); // ストライドと要素数を計算
  elems.reserve(desc.size);           // スライスのための領域を確保
  Matrix_impl::insert_flat(init, elems);
  assert(elems.size() == desc.size);
}

// from Matrix_ref
// in other words, from a reference to Matrix and a reference to the part of Matrix(partial matrix)
// (830)
template <typename T, size_t N>
template <typename U>
Matrix<T, N>::Matrix(const Matrix_ref<U, N> &x) : desc{x.desc}, elems{x.begin(), x.end()}
{
  static_assert(Convertible<U, T>(), "Matrix constructor: incompatible element types");
}

// 代入演算 from Matrix_ref: Matrix のメンバをコピー
template <typename T, size_t N>
template <typename U>
Matrix<T, N> &Matrix<T, N>::operator=(const Matrix_ref<U, N> &x)
{
  static_assert(Convertible<U, T>(), "Matrix constructor: incompatible element types");
  desc = x.desc;
  elems.assign(x.begin(), x.end());
  return *this;
}

/** C 言語スタイルによる添字演算、スライシング*/
template <typename T, size_t N> Matrix_ref<T, N - 1> Matrix<T, N>::operator[](size_t)
{
  return row(n);
}

void initialize_matrix()
{
  enum class Piece { none, cross, naught };

  Matrix<Piece, 2> board1
  {
    {
      {Piece::none, Piece::none, Piece::none}, {Piece::none, Piece::none, Piece::none},
          {Piece::none, Piece::none, Piece::none},
    }
  }
  Matrix<Piece, 2> board1(3, 3); // ok
  // Matrix<Piece, 2> board1{3, 3}; // err because constructor with initializer_list<U> is deleted
}
int main() { initialize_matrix(); }