class Vector
{
public:
  Vector(int s);
  ~Vector();
  double &operator[](int i);
  int size() const; // 関数が値を変更しないことを明示するための const

private:
  double *elem;
  int sz;
};
