constexpr int rc_max{ 4 }; // 行数と列数

class Matrix;

/*
Friend: 他のクラスの内部要素にアクセスすることができる
この例だと、
friend Vector operator*(const Matrix&, const Vector&);
は Matrix と Vector の両方の内部表現を利用することができるようになる.
*/

class Vector {
  float v[rc_max];
  friend Vector operator*(const Matrix&, const Vector&);
}

class Matrix {
  Vector v[rc_max];

  friend Vector operator*(const Matrix&, const Vector&);
}

Vector operator* (const Matrix& const Vector&) {
  Vector r;
  for (int i = 0; i != rc_max; ++i)
    // r.v[i] = 0;
    for (int j = 0; j != rc_max; ++j)
      r.v[i] += m.v[i].v[j] * v.v[j];

  return r;
}

int main() {

}