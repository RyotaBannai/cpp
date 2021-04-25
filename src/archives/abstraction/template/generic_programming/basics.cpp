#include <array>
#include <complex>
#include <iostream>
#include <list>
#include <new>
#include <string>
#include <vector>
using namespace std;

template <typename Iter, typename Val> Val sum(Iter first, Iter last)
{
  Val s = 0;
  while (first != last)
    s += *(first++);
  return s;
}

// 自作の単方向連結リスト
struct Node {
  Node *next;
  int data;
  Node(int d) { data = d; }
};

struct Node_iter {
  Node *pos;
  Node_iter(Node *n) { pos = n; }
  // prefix decrement
  Node_iter &operator++()
  {
    pos = pos->next;
    return *this;
  }
  // postfix decrement
  Node_iter operator++(int)
  {
    Node_iter old = *this;
    operator++(); // prefix decrement
    return old;
  }
  int operator*() { return pos->data; }
  bool operator!=(const Node_iter q) { return pos != q.pos; }
};

void use_sum()
{
  double ad[] = {1, 2, 3, 4};
  double sd = sum<double *, double>(ad, ad + 4); // double * は反復子になる

  array<int, 4> ai = {{1, 2, 3, 4}};
  int si = sum<int *, int>(ai.begin(), ai.end());

  cout << sd << endl;
  cout << si << endl;
}

void use_sum_node()
{
  Node n1{1};
  Node n2{2};
  Node n3{3};
  Node n4{4};
  n4.next = nullptr;
  n3.next = &n4;
  n2.next = &n3;
  n1.next = &n2;
  Node_iter node_iter{&n1};

  int sn = sum<Node_iter, int>(node_iter, nullptr);
  cout << sn << endl;
}

int main()
{
  use_sum();
  use_sum_node();
}

/*
https://www.reddit.com/r/cpp_questions/comments/3lc6om/operator_must_be_a_binary_operator_has_3/

When you are defining a binary operator outside a class, it takes two parameters:

struct Foo;
bool operator == (Foo const& a, Foo const& b);
When you define an operator inside a class, it takes one parameter, because the other is implicitly
this:

struct Foo {
    bool operator == (Foo const& a);
};

overloading operators manual:
https://en.cppreference.com/w/cpp/language/operators
*/