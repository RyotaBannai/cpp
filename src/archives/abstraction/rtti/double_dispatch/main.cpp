#include <complex>
#include <iostream>
#include <list>
#include <new>
#include <string>
#include <vector>
using namespace std;

// Forward declaration
class Circle;
class Triangle;

class Shape {
public:
  virtual bool intersect(const Shape &) const = 0;
  virtual bool intersect(const Circle &) const = 0;
  virtual bool intersect(const Triangle &) const = 0;
};

class Circle : public Shape {
public:
  bool intersect(const Shape &) const override;
  virtual bool intersect(const Circle &) const override;
  virtual bool intersect(const Triangle &) const override;
};

class Triangle : public Shape {
public:
  bool intersect(const Shape &) const override;
  virtual bool intersect(const Circle &) const override;
  virtual bool intersect(const Triangle &) const override;
};

bool Circle::intersect(const Shape &s) const
{
  cout << "intersect (circle, shape)\n";
  return s.intersect(*this);
}
bool Circle::intersect(const Circle &) const
{
  cout << "intersect (circle, circle)\n";
  return true;
}
bool Circle::intersect(const Triangle &) const
{
  cout << "intersect (circle, triangle)\n";
  return true;
}

bool Triangle::intersect(const Shape &s) const
{
  cout << "intersect (triangle, shape)\n";
  return s.intersect(*this);
}
bool Triangle::intersect(const Circle &) const
{
  cout << "intersect (triangle, circle)\n";
  return true;
}
bool Triangle::intersect(const Triangle &) const
{
  cout << "intersect (triangle, triangle)\n";
  return true;
}

// Shape を根とした Circle や Triangle など
// 任意の２つのクラスに対してこの関数を適用することを考える
void do_something(Shape &s1, Shape &s2)
{
  if (s1.intersect(s2)) {}
}

void test(Triangle &t, Circle &c)
{
  vector<pair<Shape *, Shape *>> vs{{{&t, &t}, {&t, &c}, {&c, &t}, {&c, &c}}};
  for (auto p : vs)
    p.first->intersect(*p.second);
}

int main()
{
  Triangle t{};
  Circle c{};
  test(t, c);
  /*
  The process of {&t, &c}

  p.first->intersect: Shape is called, and Shape is virtual so explores its implementation, which is
  Triangle. Therefore this ended up resolving it as triangle->intersect(Shape &s)

  s.intersect(*this): *this means Triangle, thus tries to look up shape->interface(Triangle &),
  and because it's virtual, it goes down to its implementation, which is
  circle->interface(Triangle &). Therefore, displays 'intersect (circle, triangle)'
  */
  /*
  intersect (triangle, triangle)
  intersect (triangle, circle)
  intersect (circle, triangle)
  intersect (circle, circle)
  */
}