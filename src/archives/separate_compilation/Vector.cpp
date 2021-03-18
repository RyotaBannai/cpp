#include "Vector.h"

Vector::Vector(int s) : elem{new double[s]}, sz{s}
{
  for (int i = 0; i != s; ++i)
    elem[i] = 0;
}
Vector::~Vector() { delete[] elem; } // デストラクタ ~(補数)演算子を使う
double &Vector::operator[](int i)
{
  return elem[i];
}
int Vector::size() const { return sz; }
