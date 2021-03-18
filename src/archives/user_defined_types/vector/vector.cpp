#include <iostream>
using namespace std;

// snippet(57)

struct Vector
{
  int sz;
  double *elem;
};

static void vector_init(Vector &v, int s)
// & は非 const 参照として v を受け取ることを意味する
{
  v.elem = new double[s];
  v.sz = s;
}

static double read_and_sum(int s)
{
  Vector v;
  vector_init(v, s);
  for (int i = 0; i != s; ++i)
    cin >> v.elem[i];
  double sum = 0;
  for (int i = 0; i != s; ++i)
    sum += v.elem[i];

  return sum;
}

int main()
{
  double result = read_and_sum(3);
  cout << "the result of read_and_sum " << result << endl;
}
