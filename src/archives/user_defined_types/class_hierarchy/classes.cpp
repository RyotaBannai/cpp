#include <iostream>
#include <vector>
using namespace std;

struct Point
{
  double x;
  double y;
};

// abstract class
class Shape
{
public:
  virtual Point center() const = 0; // pure virtual function
  virtual void move(Point to) = 0;
  virtual void draw() const = 0;
  virtual ~Shape(){}; // デストラクタが virtual
};

class Circle : public Shape
{
public:
  Circle(Point p, int rr); // constructor
  Point center() const { return c; }
  void move(Point to) { c = to; }
  void draw() const;
  void rotate(int);

private:
  Point c; // center
  int r;   // radius
};

class Smiley : public Circle
{
public:
  Smiley(Point p, int r) : Circle{p, r}, mouth{nullptr} {}
  ~Smiley()
  {
    delete mouth;
    for (auto p : eyes)
      delete p;
  }
  void move(Point to);
  void draw() const;
  void rotate(int);
  void add_eye(Shape *s) { eyes.push_back(s); }
  void set_mouth(Shape *s);
  virtual void wink(int i); // n 番のウインクした目

private:
  vector<Shape *> eyes; // 一般的に目は二個
  Shape *mouth;
};