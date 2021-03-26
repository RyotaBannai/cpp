#include <iostream>
#include <array>
#include <string>
using namespace std;

struct Point
{
  int x, y;
};
using Array = array<Point, 3>;

ostream &operator<<(ostream &os, Point p)
{
  return os << '{' << p.x << ',' << p.y << '}';
}

void print_points(const Point a[], int s) // s: 要素数を指定する必要がある
{
  for (int i = 0; i != s; ++i)
    cout << a[i] << endl;
}

template <typename T, unsigned long int N>
void print_points(const array<T, N> &a) // 型から要素数を判別するため要素数を指定しない
{
  for (int i = 0; i != a.size(); ++i)
    cout << a[i] << endl;
}

Array shift(Array a, Point p)
{
  for (int i = 0; i != a.size(); ++i)
  {
    a[i].x += p.x;
    a[i].y += p.y;
  }
  return a;
}

int main()
{
  Array points1{
      {{0, 1}, {2, 3}, {4, 5}}};
  int x2 = points1[2].x;
  int y2 = points1[2].y;

  Point points2[]{{0, 1}, {2, 3}, {4, 5}};

  Array ax = shift(points1, {x2, y2});

  // print_points(ax); // shifted Point
  print_points(points1);
  print_points(points2, 3);

  return 0;
}
