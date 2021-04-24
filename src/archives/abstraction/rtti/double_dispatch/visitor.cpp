#include <complex>
#include <iostream>
#include <list>
#include <new>
#include <string>
#include <vector>
using namespace std;

/*
  Visitor & 仮引数は const としない
  Visitor からの処理では、”訪れた(visited)”Node あるは、
  Visitor 自信を更新するのが一般的だからである.
*/
class Visitor;

class Node {
public:
  virtual void accept(Visitor &) = 0;
};

class Expr : public Node {
public:
  virtual void accept(Visitor &) override;
};

class Stmt : public Node {
public:
  virtual void accept(Visitor &) override;
};

class Visitor {
public:
  virtual void accept(Expr &) = 0;
  virtual void accept(Stmt &) = 0;
};

void Expr::accept(Visitor &v) { v.accept(*this); }
void Stmt::accept(Visitor &v) { v.accept(*this); }

struct Do1_visitor : public Visitor {
  void accept(Expr &) override { cout << "do1 to Expr\n"; };
  void accept(Stmt &) override { cout << "do1 to Stmt\n"; };
};

struct Do2_visitor : public Visitor {
  void accept(Expr &) override { cout << "do2 to Expr\n"; };
  void accept(Stmt &) override { cout << "do2 to Stmt\n"; };
};

Do1_visitor do1;
Do2_visitor do2;

void test(Expr &e, Stmt &s)
{
  vector<pair<Node *, Visitor *>> vn{{{&e, &do1}, {&e, &do2}, {&s, &do1}, {&s, &do2}}};
  for (auto p : vn)
    p.first->accept(*p.second);
}

int main()
{
  Expr e{};
  Stmt s{};
  test(e, s);
  /*
  do1 to Expr
  do2 to Expr
  do1 to Stmt
  do2 to Stmt
  */
}