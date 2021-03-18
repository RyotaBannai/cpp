#include <iostream>
using namespace std;

// snippet(57)

class Vector
{
public:
  Vector(int s) : elem{new double[s]}, sz{s} {} // コンストラクタ（constructor）
  double &operator[](int i) { return elem[i]; }
  int size() { return sz; }

private:
  double *elem; // 要素へのポインタ
  int sz;
};

static double read_and_sum(int s)
{
  Vector v(s);
  for (int i = 0; i != s; ++i)
    cin >> v[i];
  double sum = 0;
  for (int i = 0; i != s; ++i)
    sum += v[i];

  return sum;
}

int main()
{
  double result = read_and_sum(3);
  cout << "the result of read_and_sum " << result << endl;
}